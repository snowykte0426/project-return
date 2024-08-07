﻿#include "superclass.h"
#include "db_event.h"
#include "player_state.h"

static long long now_hp, now_mp;
static int initialized_hp = 0, initialized_mp = 0;

void initial_hp(char id[]) {
    MYSQL db;
    mysql_init(&db);
    if (!mysql_real_connect(&db, "localhost", "root", "123456", "gwangju_sword_master", 0, NULL, 0)) {
        gotoxy(42, 12);
        db_connect_error(&db);
        exit(0);
    }
    char q[255];
    sprintf(q, "SELECT hp FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
    if (mysql_query(&db, q)) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_RES* result = mysql_store_result(&db);
    if (result == NULL) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        gotoxy(42, 12);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("No data found for the given ID.");
        mysql_free_result(result);
        mysql_close(&db);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        Sleep(3000);
        exit(0);
    }
    long long max_hp = atoll(row[0]);
    if (!initialized_hp) {
        now_hp = max_hp;
        initialized_hp = 1;
    }
    gotoxy(17, 24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("[%lld/%lld]", now_hp, max_hp);
    mysql_free_result(result);
    mysql_close(&db);
    gotoxy(2, 24);
    printf("HP[■■■■■■■■■■]");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    return;
}

void initial_mp(char id[]) {
    MYSQL db;
    mysql_init(&db);
    if (!mysql_real_connect(&db, "localhost", "root", "123456", "gwangju_sword_master", 0, NULL, 0)) {
        gotoxy(42, 12);
        db_connect_error(&db);
        exit(0);
    }
    char q[255];
    sprintf(q, "SELECT mp FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
    if (mysql_query(&db, q)) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_RES* result = mysql_store_result(&db);
    if (result == NULL) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        gotoxy(42, 12);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("No data found for the given ID.");
        mysql_free_result(result);
        mysql_close(&db);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        Sleep(3000);
        exit(0);
    }
    long long max_mp = atoll(row[0]);
    if (!initialized_mp) {
        now_mp = max_mp;
        initialized_mp = 1;
    }
    gotoxy(17, 25);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    printf("[%lld/%lld]", now_mp, max_mp);
    mysql_free_result(result);
    mysql_close(&db);
    gotoxy(2, 25);
    printf("MP[■■■■■■■■■■]");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    return;
}

void now_level(char id[]) {
    MYSQL db;
    mysql_init(&db);
    if (!mysql_real_connect(&db, "localhost", "root", "123456", "gwangju_sword_master", 0, NULL, 0)) {
        gotoxy(42, 12);
        db_connect_error(&db);
        exit(0);
    }
    char q[255];
    sprintf(q, "SELECT level FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
    if (mysql_query(&db, q)) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_RES* result = mysql_store_result(&db);
    if (result == NULL) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        id_find_error(&db, result, row);
        return;
    }
    long long player_level = atoll(row[0]);
    mysql_free_result(result);
    sprintf(q, "SELECT levelup_requirement FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
    if (mysql_query(&db, q)) {
        db_query_error(&db);
        exit(0);
    }
    result = mysql_store_result(&db);
    if (result == NULL) {
        db_query_error(&db);
        exit(0);
    }
    row = mysql_fetch_row(result);
    if (row == NULL) {
        id_find_error(&db, result, row);
        return;
    }
    long long levelup_requirement = atoll(row[0]);
    mysql_free_result(result);
    sprintf(q, "SELECT levelup_point FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
    if (mysql_query(&db, q)) {
        db_query_error(&db);
        exit(0);
    }
    result = mysql_store_result(&db);
    if (result == NULL) {
        db_query_error(&db);
        exit(0);
    }
    row = mysql_fetch_row(result);
    if (row == NULL) {
        id_find_error(&db, result, row);
        return;
    }
    long long levelup_point = atoll(row[0]);
    mysql_free_result(result);
    return;
}

void now_state(char id[]) {
    MYSQL db;
    mysql_init(&db);
    if (!mysql_real_connect(&db, "localhost", "root", "123456", "gwangju_sword_master", 0, NULL, 0)) {
        gotoxy(42, 12);
        db_connect_error(&db);
        exit(0);
    }
    char q[255];
    sprintf(q, "SELECT hp,mp,speed,attack,defense,cri_chance FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
    if (mysql_query(&db, q)) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_RES* result = mysql_store_result(&db);
    if (result == NULL) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        id_find_error(&db, result, row);
        return;
    }
    gotoxy(2, 15);
    printf("HP:%s", row[0]);
    gotoxy(2, 16);
    printf("MP:%s", row[1]);
    gotoxy(2, 17);
    printf("공격력:%s", row[3]);
    gotoxy(2, 18);
    printf("방어력:%s", row[4]);
    gotoxy(2, 19);
    printf("회피률:%s%%", row[2]);
    gotoxy(2, 20);
    printf("치명타 확률:%s%%", row[5]);
    memset(q, 0, sizeof(q));
    sprintf(q, "SELECT levelup_requirement,levelup_point,level FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
    if (mysql_query(&db, q)) {
		db_query_error(&db);
		exit(0);
	}
    result = mysql_store_result(&db);
    if (result == NULL) {
        db_query_error(&db);
        exit(0);
    }
    row = mysql_fetch_row(result);
    if (row == NULL) {
		id_find_error(&db, result, row);
		return;
	}
    long long levelup_requirement = atoll(row[0]);
    long long levelup_point = atoll(row[1]);
    long long player_level = atoll(row[2]);
    mysql_free_result(result);
    gotoxy(2, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("Lv.%lld[%lld/%lld]", player_level, levelup_point, levelup_requirement);
    mysql_close(&db);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    return;
}

void hp_mp_bar(char id[]) {
    MYSQL db;
    unsigned int bar_length = 10;
    mysql_init(&db);
    if (!mysql_real_connect(&db, "localhost", "root", "123456", "gwangju_sword_master", 0, NULL, 0)) {
        gotoxy(42, 12);
        db_connect_error(&db);
        exit(0);
    }
    char q[255];
    sprintf(q, "SELECT hp,max_hp,mp,max_mp FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
    if (mysql_query(&db, q)) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_RES* result = mysql_store_result(&db);
    if (result == NULL) {
        db_query_error(&db);
        exit(0);
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        id_find_error(&db, result, row);
        return;
    }
    long long hp = atoll(row[0]);
    long long max_hp = atoll(row[1]);
    long long mp = atoll(row[2]);
    long long max_mp = atoll(row[3]);
    mysql_free_result(result);
    mysql_close(&db);
    if (hp < 100) {
        gotoxy(25, 24);
        printf(" ");
    }
    if (hp < 10) {
        gotoxy(24, 24);
        printf(" ");
    }
    gotoxy(17, 24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("[%lld/%lld]", hp, max_hp);
    gotoxy(2, 24);
    printf("HP[");
    double hp_percentage = (double)hp / max_hp;
    unsigned int filled_length = (unsigned int)(hp_percentage * bar_length);
    gotoxy(2, 24);
    printf("HP[");
    for (unsigned int i = 0; i < bar_length; i++) {
        if (i < filled_length) {
            printf("■");
        }
        else {
            printf(" ");
        }
    }
    printf("]");
    gotoxy(17, 25);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    printf("[%lld/%lld]", mp, max_mp);
    if (mp < 100) {
        gotoxy(25, 25);
        printf(" ");
    }
    if (mp < 10) {
        gotoxy(24, 25);
        printf(" ");
    }
    gotoxy(2, 25);
    printf("MP[");
    double mp_percentage = (double)mp / max_mp;
    unsigned int filled_mp_length = (unsigned int)(mp_percentage * bar_length);
	gotoxy(2, 25);
    gotoxy(2, 25);
    printf("MP[");
    for (unsigned int i = 0; i < bar_length; i++) {
        if (i < filled_mp_length) {
            printf("■");
        }
        else {
            printf(" ");
        }
    }
    gotoxy(15, 25);
    printf("]");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    return;
}