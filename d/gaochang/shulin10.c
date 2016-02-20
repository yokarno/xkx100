// Room: /d/gaochang/shulin10.c
// Last Modified by Winder on Jul. 15 2000

inherit ROOM;

void create()
{
	set("short", "�߲��Թ�");
	set("long", @LONG
������������ĳ�������ǰ�����������������Թ�֮�ڲ�����
��ָ�����㲻֪��Ҫ������·�ߡ�����ϸ���������ף����׺�ǰ������
·�϶��е������㼣�����ƺ���ʧ�˷�����ûͷ��Ӭ�㵽���Ҵ���
LONG
	);
	set("outdoors", "gaochang");
	set("no_drop",1);
	set("exits", ([
		"east" : __DIR__"shulin"+(random(8)+6),
		"west" : __DIR__"shulin"+(random(8)+6),
		"south" : __DIR__"shulin"+(random(8)+6),
		"north" : __DIR__"shulin"+(random(8)+6),
	]));
	set("objects",([
		__DIR__"npc/majiajun" : 1,
		__DIR__"npc/ghost" : 3,
	]));
	set("coor/x", -38000);
	set("coor/y", 11000);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}