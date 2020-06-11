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

struct connection_data {
    char ssid[256];
    char passwd[256];
};

#endif /* Commands_h */
