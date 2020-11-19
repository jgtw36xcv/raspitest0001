#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>

#define JOY_DEV "/dev/input/js0"

int main(void)
{	int fd, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
	char *button=NULL, name_of_joystick[80], temstr[80], pstr[256];
	struct js_event js;

	if((fd=open(JOY_DEV, O_RDONLY)) == -1)
	{	printf( "Couldn't open joystick device %s\n", JOY_DEV);
		return -1;
	}
	puts("Here we go, hit ^c to quit\n");

	ioctl(fd, JSIOCGAXES, &num_of_axis);
	ioctl(fd, JSIOCGBUTTONS, &num_of_buttons);
	ioctl(fd, JSIOCGNAME(80), &name_of_joystick);

	axis = (int *)calloc(num_of_axis, sizeof(int));
	button = (char *)calloc(num_of_buttons, sizeof(char));

	printf("Joystick detected: %s\n\t%d axis\n\t%d buttons\n\n"
		, name_of_joystick
		, num_of_axis
		, num_of_buttons);

	//fcntl(fd, F_SETFL, O_NONBLOCK);

	while(1)
	{	read(fd, &js, sizeof(struct js_event));
		switch(js.type&~JS_EVENT_INIT)
		{	case JS_EVENT_AXIS:
				axis   [ js.number ] = js.value;
				break;
			case JS_EVENT_BUTTON:
				button [ js.number ] = js.value;
				break;
			default:
				continue;
		}
		sprintf(pstr, "");
		for(x = 0; x < num_of_axis; x++)
		{	sprintf(temstr, "%c: %6d ", 65+x, axis[x]);
			strcat(pstr, temstr);
		}

		strcat(pstr, "B  ");

		for(x = 0; x < num_of_buttons; x++)
		{	sprintf(temstr, "%d: %d ", x, button[x]);
			strcat(pstr, temstr);
		}
		printf("\r%s",pstr);
		fflush(stdout);
	}
	close(fd);
	return 0;
}
