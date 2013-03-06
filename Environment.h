/*  Environment.h
 *  Created by ablumer on 2/19/13.
 *
 * DISTRIBUTED WITH PERMISSION; ALL RIGHT RESERVED TO ANSELM BLUMER
 */
// LOCSIZE defines the size of the grid in which the agent moves
// WALLSIZE defines the size of the grid giving the locations of the walls
// WALLSIZE should equal 2*LOCSIZE+1
#define LOCSIZE 3
#define WALLSIZE 7

// The available actions: move in four directions or stop (Terminate)
//            0  1  2  3  4
enum Action { N, S, E, W, T };

struct Location {
  int x, y;
};

struct ActStruct {
  bool N, S, E, W;
};

class Environment {

public:
  Environment();
  bool Goal_Test( Location loc );
  ActStruct Actions( Location loc );
  Location Result( Location loc, Action a );
  
// A wall is defined by its center point.  For example, if the agent
// starts at (0,0) and sees a wall at the north of that location, its
// center is at (0, 0.5).  This wall is specified by setting Wall[1, 2]
// to true.  In general, a wall with center at (x,y) is specified by
// setting Wall[2*x+1, 2*y+1] to true.
private:
  bool Wall[WALLSIZE][WALLSIZE];
};
