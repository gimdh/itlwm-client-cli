//
//  KernelConnector.h
//  itlwm-client
//
//  Created by gimdh on 2020/06/10.
//  Copyright © 2020 gimdh. All rights reserved.
//

#ifndef KernelConnector_h
#define KernelConnector_h

#define CONTROL_NAME "org.zxystd.itlwm.control"

#include "Commands.h"


int open_socket(void);

int send_join_ssid(const char *ssid, const char *passwd);
int send_disconnect(void);
int send_command(int id, const void *data, int data_len);

int get_nodes(struct node_data_ary *ary);
int get_command(int id, void *data, int *data_len);

int close_socket(void);

#endif /* KernelConnector_h */
