#include "headers/camDetected.h"

/*
camAsDetectcHumain permet de verifier si le programme python a
detecte si un humain est present devant la camera

input :
	none

output:
	_CAM_NOT_DETECT_ -> si personnes n'est devant la camera
	_CAM_DETECT_     -> si une personnes est devant la camera
*/
int camAsDetectcHumain() {
	int fd = 0;
	char c[20];
	int n;

	fd = open(LOCK_FILE, O_RDONLY);
	if (fd < 0) return _CAM_NOT_DETECT_;
	close(fd);

	return _CAM_DETECT_;
}