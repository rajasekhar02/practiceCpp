import copy

small_command_list = """$ cd /
$ ls
dir a
14848514 b.txt
8504156 c.dat
dir d
$ cd a
$ ls
dir e
29116 f
2557 g
62596 h.lst
$ cd e
$ ls
584 i
$ cd ..
$ cd ..
$ cd d
$ ls
4060174 j
8033020 d.log
5626152 d.ext
7214296 k"""

def createEmptyFolder():
    return {
        "sub-folders":{},
        "files":[],
        "total-size": 0
    }

def createFile( fileName, fileSize):
    return {
        "file-name": fileName,
        "file-size": fileSize
    }

def addFile(fileDict, folderStructure, context):
    if len(context) == 1:
        folderStructure[context[0]]["files"].append(fileDict)
        folderStructure[context[0]]['total-size'] = folderStructure[context[0]]['total-size'] + fileDict['file-size']
        return
    folderStructure[context[0]]["files"].append(copy.deepcopy(fileDict))
    folderStructure[context[0]]['total-size'] = folderStructure[context[0]]['total-size'] + fileDict['file-size'] # 2 BECAUSE HAVING IN THE CHILD DEST FOLDER
    addFile(fileDict, folderStructure[context[0]]["sub-folders"],context[1:len(context)])

def addFolder(folderName, folderStructure, context):
    if len(context) == 1:
        folderStructure[context[0]]["sub-folders"][folderName] = createEmptyFolder()
        return
    addFolder(folderName, folderStructure[context[0]]["sub-folders"],context[1:len(context)])

def findDirAtmost100T(folderName, folderStructure):
    currFolderSize = (folderStructure[folderName]["total-size"] <= 100000) * folderStructure[folderName]["total-size"]
    for eachSubFolderName in folderStructure[folderName]['sub-folders']:
        currFolderSize = currFolderSize + findDirAtmost100T(eachSubFolderName, folderStructure[folderName]['sub-folders'])
    return currFolderSize

def findDirAtmostGivenSpace(folderName, folderStructure, minRequiredSpace):
    currFolderSize = folderStructure[folderName]['total-size']
    for eachSubFolderName in folderStructure[folderName]['sub-folders']:
        childSize = findDirAtmostGivenSpace(eachSubFolderName, folderStructure[folderName]['sub-folders'], minRequiredSpace)
        if (childSize < currFolderSize) and ((childSize - minRequiredSpace) >= 0):
            currFolderSize = childSize
    return  currFolderSize

inputLines = input.split("\n")

stack = []
rootFileSystem = {"/":createEmptyFolder()}
set_read_lines = False
for eachInputLine in inputLines:
    [part1, *part2] = eachInputLine.split(" ")
    if part1 == '$':
        [cmd, *remaining] = part2
        if cmd == "cd":
            [folderName] = remaining         
            set_read_lines = False
            if folderName == "..":
                stack.pop()
            elif folderName == "/":
                stack = ["/"]
            else:
                stack.append(folderName)
        else:
            set_read_lines = True
        continue;
    if set_read_lines == True:
        if part1 == 'dir':
            [folderName] = part2
            addFolder(folderName,rootFileSystem,stack)
        else:
            [fileName] = part2
            newFile = createFile(fileName, int(part1))
            addFile(newFile, rootFileSystem, stack)

print(f"Part1: {findDirAtmost100T('/', rootFileSystem)}")

availableSpace = 70000000
occupiedSpace = rootFileSystem["/"]["total-size"]
freeSpace = availableSpace-occupiedSpace
requiredSpace = 30000000
deleteSpaceSize = requiredSpace - freeSpace
print(f"Part2: {findDirAtmostGivenSpace('/', rootFileSystem, deleteSpaceSize)}")
