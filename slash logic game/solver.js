let grid = [
    "-1	-1	-1	-1	-1	-1	-1	-1	-1",
    "-1	1	1	2	2	3	-1	2	-1",
    "-1	-1	3	-1	-1	-1	-1	4	-1",
    "-1	3	3	-1	1	2	-1	1	-1",
    "-1	-1	1	3	-1	-1	2	-1	2",
    "1	3	-1	2	1	-1	2	-1	0",
    "1	-1	1	-1	2	-1	-1	2	-1",
    "1	-1	-1	2	-1	-1	-1	-1	-1",
    "-1	0	-1	-1	0	-1	1	0	-1"
].map(x => x.split("	").map(y => +y));
let slashGrid = new Array(grid.length - 1).fill(0).map(x => {
    return new Array(grid.length - 1).fill(" ")
})

let isGridFilled = function (problemGrid) {
    return problemGrid.map(eachRow => {
        return eachRow.every(x => x == 0);
    }).every(x => x === true);
}

let solver = function (problemGrid, solutionGrid, solutionGridRow, solutionGridColumn, slash) {
    // am i at the end of the grid
    if (solutionGridRow === slashGrid.length - 1 && solutionGridColumn === slashGrid[0].length - 1) {
        console.log(solutionGrid.map((x, index) => [grid[index].map(y => ("" + y).padStart(2)).join("\t"), "  " + x.map(x => x.padStart(2)).join("\t")].join('\n')).join('\n'));
        //        console.log(isGridFilled(problemGrid));
        return isGridFilled(problemGrid);
    }
    // am i at the end of the row
    if (solutionGridColumn === slashGrid[0].length) {
        return solver(problemGrid, solutionGrid, solutionGridRow + 1, 0, slash);
    }

    let problemGridRow = solutionGridRow //solutionGridRow-1 < 0 ? 0: solutionGridRow-1;
    let problemGridCol = solutionGridColumn //solutionGridColumn-1 < 0 ? 0: solutionGridColumn-1;
    let newProblemGrid = JSON.parse(JSON.stringify(problemGrid));
    let newSolutionGrid = JSON.parse(JSON.stringify(solutionGrid));

    if (slash === '/') {
        if (problemGrid[problemGridRow + 1][problemGridCol] - 1 >= 0 && problemGrid[problemGridRow][problemGridCol + 1] !== 0) {
            newProblemGrid[problemGridRow + 1][problemGridCol]--;
            newSolutionGrid[solutionGridRow][solutionGridColumn] = slash;
        }
        if (problemGrid[problemGridRow][problemGridCol + 1] - 1 >= 0 && problemGrid[problemGridRow + 1][problemGridCol] !== 0) {
            newProblemGrid[problemGridRow][problemGridCol + 1]--;
            newSolutionGrid[solutionGridRow][solutionGridColumn] = slash;
        }
    } else {
        if (problemGrid[problemGridRow][problemGridCol] - 1 >= 0 && problemGrid[problemGridRow + 1][problemGridCol + 1] !== 0) {
            newProblemGrid[problemGridRow][problemGridCol]--;
            newSolutionGrid[solutionGridRow][solutionGridColumn] = slash;
        }
        if (problemGrid[problemGridRow + 1][problemGridCol + 1] - 1 >= 0 && problemGrid[problemGridRow][problemGridCol] !== 0) {
            newProblemGrid[problemGridRow + 1][problemGridCol + 1]--;
            newSolutionGrid[solutionGridRow][solutionGridColumn] = slash;
        }
    }

    solver(newProblemGrid, newSolutionGrid, solutionGridRow, solutionGridColumn + 1, "/");
    solver(newProblemGrid, newSolutionGrid, solutionGridRow, solutionGridColumn + 1, `$`);
}


solver(grid, slashGrid, 0, 0, '/');
solver(grid, slashGrid, 0, 0, `$`);