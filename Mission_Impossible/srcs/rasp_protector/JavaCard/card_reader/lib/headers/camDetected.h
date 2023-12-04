#ifndef __CAM_DETECTED_H__
#define __CAM_DETECTED_H__

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

#include "return_code.h"

#define LOCK_FILE "/tmp/protected_door.lock"

int camAsDetectcHumain();

#endif