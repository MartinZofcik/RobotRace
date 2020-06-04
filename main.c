#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "robot_race.h"

int main(){
	int n, i, obstacle_id, nRob;

	Track track;
	initTrack(&track);
	Robot robots[MAX_ROBOTS];

	printf("Zadaj sirku, vysku, pocet prekazok, robotov: ");
	scanf("%d %d %d %d", &track.width, &track.height, &track.nObs, &nRob);
	getchar();

	do{
		print(robots, nRob, &track);
		getchar();
		system("cls");
		for (i = 0;i < nRob;i++){

			obstacle_id = isCollision(&robots[i], &track);
			updateRobotDirection(&robots[i], &track, obstacle_id);
			updateRobotPosition(&robots[i]);

			if (robots[i].x >= track.height){
				printf("\nvyhral robot %c\n", i + 65);
				break;
			}
		}
	} while (1);

	return 0;
}

