#include <jni.h>
#include <string>
#include <iostream>
#include "24string.hpp"
#include "24linkList.hpp"
#include "generic_service/services/IPC_service/IPC_KE_Service_Client.cpp"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cmkcppapp_MainActivity_InitKeyExchange(
        JNIEnv *env,
        jobject /* this */) {
    std::string filename = "test";
    string cfgfile("gw_cli_Abe.cfg"), ipTablefile("IPTable.cfg");

    google::InitGoogleLogging(argv[0]);

    FLAGS_log_dir = "../logs/";

    if (CKeGateWay::Start(cfgfile, ipTablefile, OnShared))
    {
        cout << "KEP GW start failed" << endl;
        LOG(FATAL)<<"Gateway fails to start!";

        return -1;
    }
    cout << "KEP GW start success" << endl;
    LOG(INFO)<<"Gateway started.";

    /*	set shared memory*/
    struct IPC_shm *shm_c2s, *shm_s2c;

    if (IPC_shm_init(&shm_c2s, (int)0x001A, (int)1) || IPC_shm_init(&shm_s2c, (int)0x001B, (int)1))
    {
        printf("IPC Shared memory configuration error!\n");

        return -1;
    }

    //CKeGateWay::ShareWith((char*)"Bob");

    char  sessionID[65] = {0};

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