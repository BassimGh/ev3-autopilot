struct mazePoint {
	bool N;
	bool S;
	bool E;
	bool W;
};

const int lineLength = 8;
const int cols = 3;
const int rows = 3;
const int xOffset = 50;
const int yOffset = 50;

const int startx = 2;
const int starty = 0;
const int endx = 2;
const int endy = 2;
int posx = startx;
int posy = starty;

string moves[50];

mazePoint Maze[cols][rows];

void createMaze() {

	//mazePoint Maze[cols][rows];

	// init maze

	for (int row = 0; row < rows; row ++) {
		for (int col = 0; col < cols; col ++) {
			Maze[col][row].N = false;
			Maze[col][row].S = false;
			Maze[col][row].E = false;
			Maze[col][row].W = false;
		}
	}

	for (int row = 0; row < rows; row ++) {
		Maze[0][row].N = true;
		Maze[0][row].S = true;
		//Maze[cols-1][row].N = true;
		//Maze[cols-1][row].S = true;
	}

	for (int col = 0; col < cols; col ++) {
		Maze[col][0].E = true;
		Maze[col][0].W = true;
		Maze[col][rows-1].E = true;
		Maze[col][rows-1].W = true;
	}
	
	Maze[1][0].N = true;
	Maze[1][1].S = true;

	Maze[0][0].S = false;
	Maze[0][0].W = false;
	Maze[0][rows-1].N = false;
	Maze[0][rows-1].W = false;

	Maze[cols-1][0].E = false;
	Maze[cols-1][rows-1].E = false;

}

void displayMaze() {
	int x = 0;
	int y = 0;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			x = col * lineLength * 2 + xOffset;
			y = row * lineLength * 2 + yOffset;
			if (Maze[col][row].S == 1) drawLine(x, y, x, y - lineLength);
			if (Maze[col][row].N == 1) drawLine(x, y, x, y + lineLength);
			if (Maze[col][row].W == 1) drawLine(x, y, x - lineLength, y);
			if (Maze[col][row].E == 1) drawLine(x, y, x + lineLength, y);
		}
	}

	//drawEllipse(2 * startx * lineLength - lineLength/2 + xOffset,
	//						2 * starty * lineLength + lineLength/2 + yOffset,
	//						2 * startx * lineLength + lineLength/2 + xOffset,
	//						2 * starty * lineLength - lineLength/2 + yOffset);
}


struct intersection {
	int i;
	int x;
	int y;
	bool N;
	bool S;
	bool E;
	bool W;
}

void solveMaze() {
	bool solved = false;
	int pathCount;
	mazePoint path;

	intersection intersection[20];
	int intersections = 0;

	int i = 1;  // moves index

	posx = startx;
	posy = starty;

	while (i < 10){
		drawEllipse(2 * posx * lineLength - lineLength/2 + xOffset,
								2 * posy * lineLength + lineLength/2 + yOffset,
								2 * posx * lineLength + lineLength/2 + xOffset,
								2 * posy * lineLength - lineLength/2 + yOffset);
	
		pathCount = 0;

		path.N = false;
		path.S = false;
		path.E = false;
		path.W = false;

		if (posx == endx && posy == endy) {
			displayBigTextLine(1,"SOLVED");
			delay(1000);
			solved = true;
			break;
		}
		if (Maze[posx][posy].N && moves[i-1] != "S") {
			pathCount ++;
			path.N = true;
		}
		if (Maze[posx][posy].S && moves[i-1] != "N") {
			pathCount ++;
			path.S = true;
			displayBigTextLine(1,moves[i-1]);
			delay(500);
			displayCenteredTextLine(2,"");
		}
		if (Maze[posx][posy].E && moves[i-1] != "W") {
			pathCount ++;
			path.E = true;
		}
		if (Maze[posx][posy].W && moves[i-1] != "E") {
			pathCount ++;
			path.W = true;
		}

		if (pathCount < 1) {
			i = intersection[intersections - 1].i;
			posx = intersection[intersections - 1].x;
			posy = intersection[intersections - 1].y;
		}
		// else if
		if (pathCount == 1) {
			if (path.N) {
				posy ++;
				moves[i] = "N";
			}
			else if (path.S) {
				posy --;
				moves[i] = "S";
			}
			else if (path.E) {
				posx ++;
				moves[i] = "E";
			}
			else if (path.W) {
				posx --;
				moves[i] = "W";
			}
			displayCenteredTextLine(2, moves[i]);
			delay(1000);
			displayCenteredTextLine(2,"");
			i++;
		}
		else if (pathCount > 1) {
			// check if intersection is new
			bool repeated = false;
			for (int j = 0; j < intersections; j++) {
				if (intersection[j].i == i) {
					repeated = true;
				}
			}
			if (!repeated) {
				intersections ++;
				intersection[intersections - 1].i = i;
				if (path.N) {
					intersection[intersections - 1].N = true;
				}
				else if (path.S) {
					intersection[intersections - 1].S = true;
				}
				else if (path.E) {
					intersection[intersections - 1].E = true;
				}
				else if (path.W) {
					intersection[intersections - 1].W = true;
                }
			}
            if (intersections > 0) {
                if (intersection[intersections - 1].N) {
                    intersection[intersections - 1].N = false;
                    posy ++;
                    moves[i] = "N";
                }
                else if (intersection[intersections - 1].S && intersections > 0) {
                    intersection[intersections - 1].S = false;
                    posy --;
                    moves[i] = "S";
                }
                else if (intersection[intersections - 1].E && intersections > 0) {
                    intersection[intersections - 1].E = false;
                    posx ++;
                    moves[i] = "E";
                }
                else if (intersection[intersections - 1].W && intersections > 0) {
                    intersection[intersections - 1].W = false;
                    posx --;
                    moves[i] = "W";
                }
            }
		}
	}
}



task main()
{
	createMaze();
	displayMaze();
	solveMaze();

	displayCenteredTextLine(1,"done");
	displayCenteredTextLine(2, moves[2]);
	delay(500);
}


