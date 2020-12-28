

#include <jni.h>
#include<stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include<stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


using namespace std;
#include <iostream>

#include "generic_service/lower_keps/CHybridTwoWayKep.h"
#include "generic_service/lower_keps/CKemTwoWayKep.h"
#include "generic_service/kems/CHybridKem.h"
#include "generic_service/CKeGateWay.h"
#include "generic_service/kems/CRsaKem.h"
#include "generic_service/kems/CBikeKem.h"
#include "generic_service/CGatewayConfig.h"
#include <openssl/bio.h>
#include <libipc/ipc_shm_generic.h>



/*
 * GW_Alice.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */


static char *KEMs[] =
        { "RSA-KEM", "BIKE-KEM" };

static CKeGateWay *GW_Alice, *GW_Bob;

static uint8_t current_ss[1024] =
        { 0 };
static size_t ss_len = 0;
static volatile int ss_valid = 0;

void OnShared(string ss, string sessionid)
{
    static int key_id = 0;

    cout << "INFO: Shared secrets: KEY_ID = " << key_id << endl;
    //LOG(INFO)<<"Shared secretes, KEYID = "<<key_id;
    BIO_dump_fp(stdout, ss.data(), ss.length());

    memcpy(::current_ss, ss.data(), ss.length());
    ss_len = ss.length();
    if (key_id != 0)
    {
        ss_valid = 1;
    }
    key_id ++;

}


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cmkcppapp_MainActivity_InitKeyExchange(
        JNIEnv *env,
        jobject /* this */) {
    std::string filename = "test";
    string cfgfile("gw_cli_Abe.cfg"), ipTablefile("IPTable.cfg");

    //google::InitGoogleLogging(argv[0]);

    //FLAGS_log_dir = "../logs/";

    if (CKeGateWay::Start(cfgfile, ipTablefile, OnShared))
    {
        cout << "KEP GW start failed" << endl;
        //LOG(FATAL)<<"Gateway fails to start!";

        // YI wen 's orignal: return -1;
        std::string data = "-1";
        return env->NewStringUTF(data.c_str());
    }
    cout << "KEP GW start success" << endl;
    //LOG(INFO)<<"Gateway started.";

    /*	set shared memory*/
    //struct IPC_shm *shm_c2s, *shm_s2c;


    //if (IPC_shm_init(&shm_c2s, (int)0x001A, (int)1) || IPC_shm_init(&shm_s2c, (int)0x001B, (int)1))
    //{
     //   printf("IPC Shared memory configuration error!\n");
        // YI wen 's orignal: return -1;
        //return -1;
     //   std::string data = "-1";
     //   return env->NewStringUTF(data.c_str());
    //}

    //CKeGateWay::ShareWith((char*)"Bob");

    char  sessionID[65] = {0};
    size_t len;
    string sss;
    memset(sessionID, 0, sizeof(sessionID));
    printf("sessionID for IPC: %s\n", sessionID);
    CKeGateWay::ShareWith((char*)"Bob", sessionID, sss);


/*
    while (1)
    {
        size_t len;
        string sss;

        memset(sessionID, 0, sizeof(sessionID));

        if (0 == IPC_shm_read(shm_c2s, (unsigned char*)sessionID, &len))
        {
            printf("sessionID for IPC: %s\n", sessionID);
            CKeGateWay::ShareWith((char*)"Bob", sessionID, sss);
            if (0 == IPC_shm_write(shm_s2c, current_ss, ss_len))
            {
                continue;
            }
        }
    }

*/
    return env->NewStringUTF(filename.c_str());
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cmkcppapp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string filename = "QS_Encryption_key";
    return env->NewStringUTF(filename.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cmkcppapp_MainActivity_keyExchangeJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string keyStr = "biXhp3Ha1fgxVEp48zHrvVoXMStmxPuAPHo3TVz5lHU=";
    return env->NewStringUTF(keyStr.c_str());
}