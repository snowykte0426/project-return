#include "superclass.h"

void stage_3(char id[], int mop_num) {
    bool mana_recovery = false;
    Clear_Gamelog();
    static int initial_x = 32, initial_y = 17, mop_hp, mop_max_hp;
    int n = 8;
    label:;
    Monster m[10] = { oak(), bat(), oak(), wolfman(), oak(), magician(), wolfman(), Golem() };
    memset(string, 0, sizeof(string));
    setRGBColor(0, 255, 0);
    strcpy(string, "Stage.3");
    printAt(initial_x, initial_y, string);
    resetColor();
    MYSQL db;
    connect_to_db(&db);
    memset(string, 0, sizeof(string));
    strcpy(string, " ");
    scrollup_motion(initial_x, 17);
    printAt(initial_x, initial_y, string);
    gotoxy(initial_x + strlen(string), initial_y);
    char query[255];
    char event_check[30];
    memset(event_check, 0, sizeof(event_check));
    sprintf(query, "UPDATE gwangju_sword_master.account SET stage = 3, mop_num = %d WHERE id = '%s'", mop_num, id);
    if (mysql_query(&db, query)) {
        db_query_error(&db);
        mysql_close(&db);
        exit(0);
    }
    for (int i = mop_num - 1; i < n; i++) {
        strcpy(event_check, m[i].type);
        if (strcmp(event_check, "Event") == 0) {
            Whisper(id);
            MYSQL db;
            connect_to_db(&db);
            memset(query, 0, sizeof(query));
            sprintf(query, "UPDATE gwangju_sword_master.account SET mop_num = mop_num + 1 WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                mysql_close(&db);
                exit(0);
            }
            mysql_close(&db);
            continue;
        }
        else {
            unsigned char match_turn = false;
            if (i > 0) {
                scrollup_motion(initial_x, initial_y);
            }
            memset(string, 0, sizeof(string));
            srand(time(NULL));
            if (strcmp(m[i].name, "������") == 0 || strcmp(m[i].name, "������") == 0 || strcmp(m[i].name, "�����ΰ�") == 0 || strcmp(m[i].name, "��") == 0) {
                short sync = rand() % 2 + 1;
                if (sync == 1) {
                    sprintf(string, "%s�� Ƣ��Դ�!", m[i].name);
                }
                else {
                    sprintf(string, "%s�� ��Ÿ����!", m[i].name);
                }
            }
            else {
                short sync = rand() % 2 + 1;
                if (sync == 1) {
                    sprintf(string, "%s�� Ƣ��Դ�!", m[i].name);
                }
                else {
                    sprintf(string, "%s�� ��Ÿ����!", m[i].name);
                }
            }
            gotoxy(50, 21);
            printf("                                                           ");
            scrollup_motion(initial_x, 17);
            printAt(initial_x, initial_y, string);
            mop_max_hp = mop_hp = m[i].hp;
            while (true) {
                sprintf(query, "SELECT max_mp,mp FROM gwangju_sword_master.user_state WHERE id = '%s'", id);
                if (mysql_query(&db, query)) {
                    db_query_error(&db);
                    mysql_close(&db);
                    exit(1);
                }
                MYSQL_RES* res = mysql_store_result(&db);
                MYSQL_ROW row = mysql_fetch_row(res);
                int mp_max = atoi(row[0]);
                int mp = atoi(row[1]);
                mysql_free_result(res);
                memset(query, 0, sizeof(query));
                int mp_reco = mp + 10 > mp_max ? mp_max - mp : 10;
                if (mana_recovery) {
                    memset(query, 0, sizeof(query));
                    sprintf(query, "UPDATE gwangju_sword_master.user_state SET mp = mp+%d WHERE id = '%s'", mp_reco, id);
                    if (mysql_query(&db, query)) {
                        db_query_error(&db);
                        mysql_close(&db);
                        exit(0);
                    }
                }
                mana_recovery = true;
                if (!mysql_ping(&db)) {
                    connect_to_db(&db);
                }
                gotoxy(50, 21);
                printf("                                           ");
                mop_hp_bar(mop_hp, mop_max_hp, 50, 21, m[i].name);
                ClearViewState();
                now_level(id);
                now_state(id);
                hp_mp_bar(id);
                long long b = ingame_select(id, m, turn, initial_x, initial_y);
                if (b == 1831) {
                    mop_num++;
                    break;
                }
                else if (b == 1023914) {
                    i = -1;
                    mop_num = 1;
                    goto label;
                    continue;
                }
                else {
                    short sync = 0;
                    mop_hp -= b;
                    turn++;
                    match_turn = true;
                    if (mop_hp > 0) {
                        if (match_turn == true) {
                            sync = mop_turn(id, m, i, initial_x, initial_y);
                        }
                        if (sync) {
                            mop_hp += 5;
                            memset(query, 0, sizeof(query));
                            sprintf(query, "UPDATE gwangju_sword_master.user_state SET hp = hp - 5 WHERE id = '%s'", id);
                            if (mysql_query(&db, query)) {
                                db_query_error(&db);
                                mysql_close(&db);
                                exit(0);
                            }
                        }
                        continue;
                    }
                    else if (mop_hp <= 0) {
                        memset(string, 0, sizeof(string));
                        setRGBColor(255, 255, 51);
                        sprintf(string, "%s�� óġ�ߴ�!", m[i].name);
                        drop_booty(id, m[i].name);
                        scrollup_motion(initial_x, 17);
                        printAt(initial_x, initial_y, string);
                        gotoxy(initial_x + strlen(string), initial_y);
                        resetColor();
                        memset(query, 0, sizeof(query));
                        sprintf(query, "UPDATE gwangju_sword_master.account SET mop_num = mop_num + 1 WHERE id = '%s'", id);
                        if (mysql_query(&db, query)) {
                            db_query_error(&db);
                            mysql_close(&db);
                            exit(0);
                        }
                        event:;
                        if (mop_num == 2) {
                            Clear_Gamelog();
                            gotoxy(50, 21);
                            printf("                                              ");
                            Rooting_conn(id);
                            memset(query, 0, sizeof(query));
                            Clear_Gamelog();
                        }
                        if (mop_num == 8) {
                            Clear_Gamelog();
                            gotoxy(50, 21);
                            printf("                                                  ");
                            Mimic_conn(id);
                            memset(query, 0, sizeof(query));
                            Clear_Gamelog();
                        }
                        mop_num++;
                        break;
                    }
                }
            }
            check_and_delete_expired_effects_fug(id, &db);
            Effect_Counter(id);
        }
    }
    mysql_close(&db);
    gotoxy(50, 21);
    printf("                                              ");
    stage3_clear(id);
    stage_4(id, 1);
}

void stage3_clear(char id[]) {
    MYSQL db;
    gotoxy(50, 21);
    printf("                                           ");
    connect_to_db(&db);
    Clear_Gamelog();
    char query[255];
    unsigned int line = 0;
    unsigned int final_y = 2;
    memset(query, 0, sizeof(query));
    const char* text = "������ ����� ���տ� �ֽ��ϴ�.\n"
        "������ ������ �� ���������� ���������� �ְ�\n"
        "������ ���� ������ �ǿ� �𸣴� ���� ��ü�� �����մϴ�.\n"
        "�������� ���� �� ������ �������� ���� ������ �����Դϴ�.\n"
        "���ϵ� ������ �ʾҵ� ��ſ��� �ο��� ����� ��������� �ֽ��ϴ�.\n"
        "���� ����� �������ϴ�...";
    int console_width = 120 - 32 + 1;
    int console_height = 17 - 2 + 1;
    int start_x = 32;
    int start_y = 2;
    unsigned int text_length = strlen(text);
    unsigned int i = 0;
    while (i < text_length) {
        int current_x = start_x;
        int current_y = start_y + line;
        int line_length = 0;
        while (i + line_length < text_length && text[i + line_length] != '\n' && line_length < console_width) {
            line_length++;
        }
        current_x = start_x + (console_width - line_length) / 2;
        gotoxy(current_x, current_y);
        for (int j = 0; j < line_length; j++) {
            printf("%c", text[i + j]);
            fflush(stdout);
            Sleep(50);
        }
        i += line_length;
        if (text[i] == '\n') {
            i++;
        }
        line++;
        if (line >= console_height) {
            break;
        }
    }
    final_y = start_y + line;
    const char* hp_recovered_text = "[HP�� �ִ�ġ���� ȸ���Ǿ����ϴ�]";
    int hp_recovered_x = start_x + (console_width - strlen(hp_recovered_text)) / 2;
    gotoxy(hp_recovered_x, final_y + 1);
    setRGBColor(0, 255, 0);
    printf("%s", hp_recovered_text);
    resetColor();
    int message_x = start_x + (console_width - 27) / 2;
    gotoxy(message_x, final_y + 4);
    Sleep(1975);
    printf("����Ϸ��� Enter�� ��������");
    CursorView(0);
    while (true) {
        int n = KeyControl();
        if (n == SUBMIT) {
            sprintf(query, "UPDATE gwangju_sword_master.account SET stage = 2, mop_num = 1 WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                mysql_close(&db);
                exit(0);
            }
            memset(query, 0, sizeof(query));
            sprintf(query, "UPDATE gwangju_sword_master.user_state SET hp = max_hp WHERE id = '%s'", id);
            if (mysql_query(&db, query)) {
                db_query_error(&db);
                mysql_close(&db);
                exit(0);
            }
            mysql_close(&db);
            return;
        }
        else {
            continue;
        }
    }
}