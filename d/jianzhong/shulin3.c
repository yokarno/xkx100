//Room: songlin2.c ���� 
//Date: Sep 22 1997

inherit ROOM;

void create()
{
      set("short","����");
      set("long",@LONG
������������������գ�������ֻ�о�������ǰ�󵽴�
������Ӱ��һ��СϪ�������У������������š�
LONG);
      set("outdoors", "jianzhong");
      set("exits",([ /* sizeof() == 1 */
          "north"  : __DIR__"shulin4",
	  "east"   : __DIR__"shulin3",
	  "west"   : __DIR__"shulin2",
          "south"  : __DIR__"shulin1", 
      ]));
	set("coor/x", -400);
	set("coor/y", -470);
	set("coor/z", 0);
	setup();
      replace_program(ROOM);
}