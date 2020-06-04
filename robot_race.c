#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "robot_race.h"


void initTrack(Track* track) {

	int i, k = 0;
	srand(time(NULL));
	k = rand() % 3 + 2;

	for (i = 0;i < track->nObs;i++){
		track->a_Obs[i].hei = 2;
		track->a_Obs[i].wid = 2 + rand() / (RAND_MAX / (4 - 2 + 1) + 1);
		track->a_Obs[i].x = k;
		track->a_Obs[i].y = 1 + rand() / (RAND_MAX / ((track->width) - 3) + 1);

		k += 3;
	}
}

void initRobots(Robot robots[], int n, Track* track){
	int i, k = 1;

	for (i = 0;i < n;i++){
		robots[i].direction = 0;
		robots[i].speed = ROBOT_SPEED;
		robots[i].x = 0;
		robots[i].y = k;
		k += track->width / n;
	}
}


int isCollision(Robot* robot, Track* track){
	int i;
	for (i = 0; i < track->nObs; i++){

		if (robot->y + 1 == track->width && robot->direction == 1)
			return(-1);
		if (robot->y - 1 == 0 && robot->direction == -1 && robot->y < track->a_Obs[i].y)
			return(-1);
		if (robot->x == track->a_Obs[i].x - 1 && (robot->y >= track->a_Obs[i].y && robot->y < (track->a_Obs[i].y + track->a_Obs[i].wid)))
			return 0;
		if (robot->x == track->a_Obs[i].x - 1 && robot->y <= track->a_Obs[i].y)
			return(-2);
		if (robot->x == track->a_Obs[i].x - 1 && robot->y > (track->a_Obs[i].y + track->a_Obs[i].wid))
			return(-2);
	}
	return -2;
}


void updateRobotPosition(Robot* robot)
{
	if (robot->direction == 0)
		robot->x += robot->speed;

	if (robot->direction == 1)
		robot->y += robot->speed;

	if (robot->direction == (-1))
		robot->y -= robot->speed;
}


void updateRobotDirection(Robot* robot, Track* track, int obstacle_id){

	if (obstacle_id == (-2))
		robot->direction = 0;

	if (obstacle_id == -1)
		robot->direction = -1;

	if (obstacle_id == -1 && robot->direction == 0 && robot->y >= track->width)
		robot->direction = -1;

	if (obstacle_id == 0 && robot->direction == 0)
		robot->direction = 1;


	if (obstacle_id == 0 && robot->direction == 1)
		robot->direction = 1;

	if (obstacle_id == 0 && robot->direction == -1)
		robot->direction = -1;
}


void print(Robot robots[], int n, Track* track){
	int dlzka, sirka;
	int i, y, x;

	int znak = -10;
	for (x = 0;x < track->height;++x){
		for (y = 0;y < track->width + 2;++y){

			if (y == 0 || y == track->width)
				znak = -2;


			for (i = 0;i < track->nObs;++i){
				dlzka = track->a_Obs[i].wid + track->a_Obs[i].y;
				sirka = track->a_Obs[i].hei + track->a_Obs[i].x;

				if ((y >= track->a_Obs[i].y && y < dlzka) && (x >= track->a_Obs[i].x && x < sirka)) 
					znak = -1;
			}


			if (znak != -2 || znak != -1){

				for (i = 0;i < n;++i){
					if (robots[i].x == x && robots[i].y == y)
						znak = i;
				}
			}
			if (znak == -2)
				printf("|");

			if (znak == -1)
				printf("*");

			if (znak >= 0)
				printf("%c", znak + 65);

			if (znak < -2)

				printf(" ");
			znak = -10;
		}
		printf("\n");
	}
}
