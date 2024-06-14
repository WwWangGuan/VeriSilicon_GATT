//
// Created by WwWangGuanHeR on 2024/6/14 0014.
//

#include "PrivateGATT.h"

// 特性值定义
static uint8_t speech_raw_data_value[512];
static uint8_t speech_recognition_result_value[64];

// 读特性函数
static ssize_t read_speech_raw_data(struct bt_conn *conn,
                                    const struct bt_gatt_attr *attr,
                                    void *buf, uint16_t len,
                                    uint16_t offset) {
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                             sizeof(speech_raw_data_value));
}

static ssize_t read_speech_recognition_result(struct bt_conn *conn,
                                              const struct bt_gatt_attr *attr,
                                              void *buf, uint16_t len,
                                              uint16_t offset) {
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                             sizeof(speech_recognition_result_value));
}


static void blvl_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{

}

BT_GATT_SERVICE_DEFINE(VSRS, BT_GATT_PRIMARY_SERVICE(BT_UUID_VSRS),
                       BT_GATT_CHARACTERISTIC(BT_UUID_VSRS_C1,
                                              BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                                              BT_GATT_PERM_READ_ENCRYPT, read_speech_raw_data, NULL,
                                              speech_raw_data_value),
                       BT_GATT_CCC(blvl_ccc_cfg_changed, BT_GATT_PERM_READ),
                       BT_GATT_CHARACTERISTIC(BT_UUID_VSRS_C2,
                                              BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                                              BT_GATT_PERM_READ_ENCRYPT, read_speech_recognition_result, NULL,
                                              speech_recognition_result_value),
                       BT_GATT_CCC(blvl_ccc_cfg_changed, BT_GATT_PERM_READ),);
