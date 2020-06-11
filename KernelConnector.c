//
//  KernelConnector.c
//  itlwm-client
//
//  Created by gimdh on 2020/06/10.
//  Copyright © 2020 gimdh. All rights reserved.
//

#include "KernelConnector.h"

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/kern_control.h>
#include <sys/kern_event.h>
#include <unistd.h>
#include <string.h>

static int fd = -1;
static int id = -1;

int open_socket(void)
{

    fd = socket(PF_SYSTEM, SOCK_DGRAM, SYSPROTO_CONTROL);
    printf("fd %d\n", fd);
    fflush(stdout);

    if (fd != -1) {
        struct sockaddr_ctl addr;

        memset(&addr, 0, sizeof(addr)); // sets the sc_unit field to 0
        addr.sc_len = sizeof(addr);
        addr.sc_family = AF_SYSTEM;
        addr.ss_sysaddr = AF_SYS_CONTROL;

        struct ctl_info info;
        memset(&info, 0, sizeof(info));
        strncpy(info.ctl_name, CONTROL_NAME, sizeof(info.ctl_name));

        if (ioctl(fd, CTLIOCGINFO, &info)) {
            fprintf(stderr, "Could not get ID for kernel control.\n");
            return -1;
        }

        id = info.ctl_id;
        addr.sc_id = info.ctl_id;
        addr.sc_unit = 0;

        int result = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
        if (result) {
            fprintf(stderr, "connect failed %d\n", result);
            return -1;
        }

    } else { /* no fd */
        fprintf(stderr, "failed to open socket\n");
        return -1;
    }
    
    return 0;
}

int send_join_ssid(const char *ssid, const char *passwd) {
    struct connection_data data;
    
    strcpy(data.ssid, ssid);
    strcpy(data.passwd, passwd);
    
    return send_command(COM_JOIN, (void*) &data, sizeof(struct connection_data));
}

int send_disconnect(void) {
    return send_command(COM_DISCON, NULL, 0);
}

int send_command(int id, const void *data, int data_len) {
    if (fd == -1)
    {
        open_socket();
    }
    

    int result = setsockopt(fd, SYSPROTO_CONTROL, id, data, data_len);
    int a = errno;

    if (result) {
        fprintf(stderr, "setsockopt failed on call id %d - result was %d\n", id, result);
        return a;
    }
    
    return 0;
}

int get_nodes(struct node_data_ary *ary) {
    int len = sizeof(struct node_data_ary);
    return get_command(COM_GETLIST, ary, &len);
}

int get_command(int id, void *data, int *data_len) {
    if (fd == -1)
    {
        open_socket();
    }

    int result = getsockopt(fd, SYSPROTO_CONTROL, id, data, data_len);
    int a = errno;

    if (result) {
        fprintf(stderr, "getsockopt failed on call id %d - result was %d\n", id, result);
        return a;
    }

    return 0;
}

int close_socket(void) {
    return close(fd);
}
