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

large_input = """Valve JC has flow rate=0; tunnels lead to valves XS, XK
Valve TK has flow rate=0; tunnels lead to valves AA, RA
Valve PY has flow rate=0; tunnels lead to valves UB, MW
Valve XK has flow rate=15; tunnels lead to valves CD, JC, TP, UE
Valve EI has flow rate=6; tunnels lead to valves UB, HD
Valve OV has flow rate=0; tunnels lead to valves QC, WK
Valve CX has flow rate=3; tunnels lead to valves ZN, AM, OE, YS, QE
Valve YS has flow rate=0; tunnels lead to valves QC, CX
Valve DC has flow rate=0; tunnels lead to valves UE, NM
Valve EA has flow rate=5; tunnels lead to valves QE, XO, GX
Valve VE has flow rate=0; tunnels lead to valves YH, NM
Valve RN has flow rate=0; tunnels lead to valves WK, NU
Valve VJ has flow rate=0; tunnels lead to valves QC, CS
Valve HD has flow rate=0; tunnels lead to valves JI, EI
Valve UB has flow rate=0; tunnels lead to valves EI, PY
Valve XS has flow rate=17; tunnels lead to valves JC, CE
Valve AM has flow rate=0; tunnels lead to valves NU, CX
Valve GX has flow rate=0; tunnels lead to valves EA, RA
Valve UI has flow rate=0; tunnels lead to valves NC, ZG
Valve NM has flow rate=22; tunnels lead to valves DC, VE, DX
Valve CE has flow rate=0; tunnels lead to valves XS, WD
Valve NC has flow rate=25; tunnels lead to valves UI, VQ
Valve TP has flow rate=0; tunnels lead to valves XK, RA
Valve ZN has flow rate=0; tunnels lead to valves CX, XI
Valve CS has flow rate=0; tunnels lead to valves AA, VJ
Valve MW has flow rate=23; tunnel leads to valve PY
Valve AA has flow rate=0; tunnels lead to valves TK, WC, CS, AL, MS
Valve RA has flow rate=4; tunnels lead to valves WD, TP, TK, GX, JI
Valve NU has flow rate=10; tunnels lead to valves DU, AM, RN, HS, AL
Valve QE has flow rate=0; tunnels lead to valves CX, EA
Valve AH has flow rate=0; tunnels lead to valves WK, MS
Valve YH has flow rate=20; tunnels lead to valves VE, CD
Valve SH has flow rate=0; tunnels lead to valves DU, ZG
Valve OE has flow rate=0; tunnels lead to valves WC, CX
Valve XO has flow rate=0; tunnels lead to valves EA, ZG
Valve JI has flow rate=0; tunnels lead to valves RA, HD
Valve XI has flow rate=0; tunnels lead to valves WK, ZN
Valve HS has flow rate=0; tunnels lead to valves QC, NU
Valve VQ has flow rate=0; tunnels lead to valves WK, NC
Valve UE has flow rate=0; tunnels lead to valves XK, DC
Valve YP has flow rate=19; tunnel leads to valve DX
Valve WD has flow rate=0; tunnels lead to valves CE, RA
Valve DX has flow rate=0; tunnels lead to valves NM, YP
Valve ZG has flow rate=11; tunnels lead to valves UI, SH, XO
Valve MS has flow rate=0; tunnels lead to valves AA, AH
Valve QC has flow rate=9; tunnels lead to valves HS, VJ, OV, YS
Valve DU has flow rate=0; tunnels lead to valves NU, SH
Valve WK has flow rate=12; tunnels lead to valves RN, XI, VQ, OV, AH
Valve CD has flow rate=0; tunnels lead to valves YH, XK
Valve AL has flow rate=0; tunnels lead to valves AA, NU
Valve WC has flow rate=0; tunnels lead to valves OE, AA"""

list_of_valves_str = large_input.split("\n")

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

# print(dist)

for r in vertices:
    for u in vertices:
        for v in vertices:
            if dist[u][v] > (dist[u][r] + dist[r][v]):
                dist[u][v] = dist[u][r] + dist[r][v]

# print(dist)

valve_pressure_zero = []
for key in list(valve_pressure):
    # print(key, valve_pressure[key])
    if valve_pressure[key] == 0:
        valve_pressure_zero.append(key)

time = 0
curr_position = "AA"
total_pressure = 0
incrementer = 0
temp_valve_pressure = copy.deepcopy(valve_pressure)
visited_valves = set()
while time < 30 and len(visited_valves) < len(valve_pressure):
    available_valves = []
    for key in list(dist[curr_position]):
        if key == curr_position:
            continue
        available_valves.append(
            {
                "position": key,
                "pressure": temp_valve_pressure[key],
                "time_taken": dist[curr_position][key],
                "heuristic_value": round(
                    temp_valve_pressure[key] / dist[curr_position][key]
                ),
            }
        )
    available_valves = sorted(
        available_valves,
        key=lambda x: (x["heuristic_value"], -1 * x["time_taken"]),
        reverse=True,
    )
    curr_position = available_valves[0]["position"]
    temp_valve_pressure[curr_position] = 0
    visited_valves.add(curr_position)
    if time < time - available_valves[0]["time_taken"]:
        total_pressure = total_pressure + (30 - time) * incrementer
    time = time + available_valves[0]["time_taken"]
    if available_valves[0]["pressure"] > 0:
        time += 1
    total_pressure = total_pressure + (
        (available_valves[0]["time_taken"] + 1) * incrementer
    )
    incrementer += available_valves[0]["pressure"]
print(total_pressure)
