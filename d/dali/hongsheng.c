//Room: /d/dali/hongsheng.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","��ʥ����");
	set("long",@LONG
��ʥ����������һ�����������ڲ�ɽ֮´�����������Ϊ������
������֮һ����ʥ����Ϊ�ķ��ο���שʯ������������֮����ש����
��ɬ����ʹ���ĽǷ��̡��������������������ߣ�����������
LONG);
	set("outdoors", "dalin");
	set("exits",([ /* sizeof() == 1 */
	    "west"      : __DIR__"cangshan",
	    "enter"     : __DIR__"hongsheng1",
	    "south"     : "/d/tianlongsi/damen",
	]));
	set("no_clean_up", 0);
	set("coor/x", -37000);
	set("coor/y", -56000);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}