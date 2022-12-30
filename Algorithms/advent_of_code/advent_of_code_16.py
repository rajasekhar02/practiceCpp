import re
import copy
import queue
from dataclasses import dataclass, field
from typing import Any


small_input = """Valve AA has flow rate=0; tunnels lead to valves DD, II, BB
Valve BB has flow rate=13; tunnels lead to valves CC, AA
Valve CC has flow rate=2; tunnels lead to valves DD, BB
Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE
Valve EE has flow rate=3; tunnels lead to valves FF, DD
Valve FF has flow rate=0; tunnels lead to valves EE, GG
Valve GG has flow rate=0; tunnels lead to valves FF, HH
Valve HH has flow rate=22; tunnel leads to valve GG
Valve II has flow rate=0; tunnels lead to valves AA, JJ
Valve JJ has flow rate=21; tunnel leads to valve II"""


list_of_valves_str = small_input.split("\n")

valve_pressure = {}
adj_list = {}

for each_str in list_of_valves_str:
    matches = re.search(
        "Valve (.+?) has flow rate=(.+?); (tunnel|tunnels) (lead|leads) to (valve|valves) (.+)",
        each_str,
    )
    # print(matches.group(1), matches.group(2), matches.group(6))
    valve_pressure[matches.group(1)] = int(matches.group(2))
    adj_list[matches.group(1)] = sorted(
        [i.strip() for i in matches.group(6).split(",")]
    )


# print(valve_pressure, adj_list)
dist = {}
vertices = list(valve_pressure)
for u in vertices:
    dist[u] = {}
    for v in vertices:
        if u == v:
            dist[u][v] = 0
        elif v in adj_list[u]:
            dist[u][v] = 1
        else:
            dist[u][v] = 99999


valve_pressure_zero = []
for key in list(valve_pressure):
    # print(key, valve_pressure[key])
    if valve_pressure[key] == 0:
        valve_pressure_zero.append(key)
    # valve_pressure_opened[key] = True if valve_pressure[key] == 0 else False

sample_visiting_nodes = {}

for key in list(valve_pressure):
    # print(key, valve_pressure[key])
    sample_visiting_nodes[key] = 4 * len(adj_list[key])
# print(valve_pressure_opened)
class State(object):
    node = "AA"
    pressure = 0
    incrementer = 0
    time = 30
    opened_valves = copy.deepcopy(valve_pressure_zero)
    visited_nodes = copy.deepcopy(sample_visiting_nodes)

    def __lt__(self, obj):
        """self < obj."""
        return self.heuristic() < obj.heuristic()

    def __le__(self, obj):
        """self <= obj."""
        return self.heuristic() <= obj.heuristic()

    def __eq__(self, obj):
        """self == obj."""
        return self.heuristic() == obj.heuristic()

    def __ne__(self, obj):
        """self != obj."""
        return self.heuristic() != obj.heuristic()

    def __gt__(self, obj):
        """self > obj."""
        return self.heuristic() > obj.heuristic()

    def __ge__(self, obj):
        """self >= obj."""
        return self.heuristic() >= obj.heuristic()

    def __cmp__(self, other):
        return self.heuristic() > other.heuristic()

    def heuristic(self):
        return self.pressure + self.incrementer


init_state = State()

task_queue = queue.PriorityQueue()
task_queue.put(init_state)

max_pressure = 0

while not task_queue.empty():
    state = task_queue.get()
    if state.time == 0:
        state_pressure = -1 * state.pressure
        if max_pressure < state_pressure:
            max_pressure = state_pressure
            print(max_pressure)
        continue

    if len(state.opened_valves) == len(adj_list):
        state_pressure = -1 * (state.pressure + state.incrementer * state.time)
        max_pressure = max(max_pressure, state_pressure)
        continue

    if state.node not in state.opened_valves:
        new_state = State()
        new_state.node = state.node
        new_state.incrementer = state.incrementer - valve_pressure[state.node]
        new_state.pressure = state.pressure + new_state.incrementer
        new_state.time = state.time - 1
        new_state.opened_valves = copy.deepcopy(state.opened_valves)
        new_state.opened_valves.append(state.node)
        task_queue.put(new_state)

    for i in adj_list[state.node]:
        new_state = State()
        new_state.node = i
        new_state.incrementer = state.incrementer
        new_state.pressure = state.pressure + new_state.incrementer
        new_state.time = state.time - 1
        new_state.opened_valves = copy.deepcopy(state.opened_valves)
        # new_state.visited_nodes = copy.deepcopy(state.visited_nodes)
        # new_state.visited_nodes[i] -= 1
        # if new_state.visited_nodes[i] < 0:
        #     continue
        task_queue.put(new_state)

print(max_pressure)
