//
//  Commands.h
//  itlwm-client
//
//  Created by gimdh on 2020/06/10.
//  Copyright © 2020 gimdh. All rights reserved.
//

#ifndef Commands_h
#define Commands_h

#define COM_JOIN 1
#define COM_DISCON 2
#define COM_GETLIST 3

struct connection_data {
    char ssid[256];
    char passwd[256];
};

struct node_data {
    char essid[256];
    char bssid[32];
    int rssi;
};

struct node_data_ary {
    int len;
    struct node_data node[64];
};

#endif /* Commands_h */