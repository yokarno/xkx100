// Room: /d/gaibang/xxandao2.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����ؤ�Ｋ�����ܵĵ���ͨ��������ؤ�Ｘ����֮��Ѫ��ɡ� 
LONG );
	set("exits", ([
		"west" : __DIR__"underxx",
		"east" : __DIR__"xxandao1",
	]));
	set("no_clean_up", 0);
	set("coor/x", -10000);
	set("coor/y", 500);
	set("coor/z", -20);
	setup();
	replace_program(ROOM);
}