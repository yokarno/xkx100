// /cmds/skill/learn.c

// Modified by Constant Jan 11 2001

inherit F_CLEAN_UP;

#include <skill.h>
#include <ansi.h>


string *reject_msg = ({
	"˵������̫�����ˣ�����ô�ҵ���\n",
	"�����ܳ�����һ����˵������̣�����ô�ҵ���\n",
	"Ц��˵��������Ц�ˣ��������С�������ʸ�ָ�㡹��ʲô��\n",
});

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string skill, teacher, master, skill_name;
	object ob;
	int master_skill, my_skill, jing_cost, times, pertimes;
	int improve_points;
	 mixed flag;
	 int i;
	 
	if (me->is_busy())
		return notify_fail("��������æ���ء�\n");
	if (environment(me)->is_chat_room())
	  return notify_fail("�����ֹ������\n");
	if(!arg || (sscanf(arg, "%s %s %d", teacher, skill, times)!=3 ))
		return notify_fail("ָ���ʽ��learn|xue <ĳ��> <����> <����>\n");
	if (times < 1 || times > 100)
		return notify_fail("ѧϰ��������һ�Σ����Ҳ���ܳ���һ�ٴΡ�\n");
	if( me->is_fighting() )
		return notify_fail("����ĥǹ������������\n");
	if( !(ob = present(teacher, environment(me))) || !ob->is_character())
		return notify_fail("��Ҫ��˭��̣�\n");
	if( !living(ob) || ob->query_temp("noliving") )
		return notify_fail("��....����Ȱ�"+ob->name()+"Ū����˵��\n");

  notify_fail( ob ->name() + reject_msg[random(sizeof(reject_msg))] );
	if( !me->is_apprentice_of(ob) && !(ob->recognize_apprentice(me,skill)) )
	{
		return	0;	
	}
	if( !master_skill = ob->query_skill(skill, 1) )
		return notify_fail("���������±����ұ���ѧ�ˡ�\n");

	if (stringp(flag = ob->query("no_teach/" + skill)))
	{
		message_vision(CYN "$N" CYN "ҡҡͷ��˵����" + flag + "\n" NOR, ob);
		return 1;
	} else
	if (intp(flag) && flag)
	{
		if (flag != 1)
			// show the messaeg if the result was not -1
			write(CYN + ob->name() + CYN "˵�����Բ���" +
				to_chinese(skill) + "�ɲ�����㴫�ڡ�\n" NOR);
					return 1;
	}

  notify_fail(ob->name() + "��Ը���������ܡ�\n");
	if( ob->prevent_learn(me, skill) )
		return 0;
	my_skill = me->query_skill(skill, 1);
	if( my_skill >= master_skill )
		return notify_fail("�������ĳ̶��Ѿ�������ʦ���ˡ�\n");
	if( my_skill >= (int)(master_skill - me->query("betrayer")*2))
		return notify_fail(ob->name() +"������üͷ�������������ȥ����ʦ������\n");
	if ( userp(ob) && my_skill >= 200 )
		return notify_fail("����Ŀǰ���������Ѳ��������ѧϰ�ˡ�\n");
	if ((SKILL_D(skill)->type())!="knowledge" && my_skill >= 250)
	  return notify_fail(ob->name() + "˵������" + to_chinese(skill) +"�Ĺ����Ѿ��Ƿ�ͬ�����ˣ��ҾͲ��ٽ��㣬���Լ����о��ɡ�\n");
	notify_fail("����Ŀǰ��������û�а취ѧϰ���ּ��ܡ�\n");
	if( !SKILL_D(skill)->valid_learn(me) ) 
	return 0;

	jing_cost = 150 / (int)me->query("int");
	if( !my_skill )
	{
		jing_cost *= 2;
		me->set_skill(skill,0);
	}

	if( (me->query("potential") - me->query("learned_points")) < times )
		return notify_fail("���Ǳ�ܲ���ѧϰ��ô����ˡ�\n");
	printf(HIC"����%s�����"+chinese_number(times)+"���йء�%s�������ʡ�\n"NOR, ob->name(), to_chinese(skill));
	if( ob->query("env/no_teach") )
		return notify_fail("����" + ob->name() + "���ڲ���׼���ش�������⡣\n");
	tell_object(ob, sprintf("%s��������йء�%s�������⡣\n",
		me->name(), to_chinese(skill)));
	if (userp(ob))
	if(  (int)ob->query("jing") > jing_cost*times/5 + 1 )
	{
		  ob->receive_damage("jing", jing_cost/5 + 1);
	}
	else
	{
		write("����" + ob->name() + "��Ȼ̫���ˣ�û�а취����ʲô��\n");
		tell_object(ob, "������̫���ˣ�û�а취��"+me->name()+"��\n");
		return 1;
	}
		if( (string)SKILL_D(skill)->type()=="martial" &&
		my_skill*my_skill*my_skill/10 > (int)me->query("combat_exp") )
		{
			return notify_fail("Ҳ����ȱ��ʵս���飬���"+ob->name()+"�Ļش������޷���ᡣ\n");
		}
    if (!me->query("env/auto_regenerate") && 
        				me->query("jing")< jing_cost * times)
							return notify_fail("�����̫���ˣ����ʲôҲû��ѧ����\n");
//	if( (int)me->query("jing") > jing_cost * times )
			for (pertimes = 0; pertimes < times ; pertimes ++)
			{
				if ((int)me->query("jing") < jing_cost)
        {
            if (me->query("env/auto_regenerate") &&
                SKILL_D("force/regenerate")->exert(me, me))
              {
              // try to regenerate & learn again
               write("����þ������һЩ����������ѧϰ��\n");
               pertimes--;
                continue;
            } else
              {
//             me->set("jing", 0);
             break;
              }
        }
 				me->receive_damage("jing", jing_cost );    
				me->add("learned_points", 1);

			}
			if (pertimes>0)
			{
				for (i=0;i<pertimes;i++)
				{
// ѧϰ�ٶ� = �������Լ����������Եĺ͵�һ�룬���书ѧϰ������
// δ����ѧϰ�����ļ��ܣ�Ĭ��ѧϰ����Ϊ10��
					improve_points = (me->query_int()+me->query("int"))/2;
					if(SKILL_D(skill)->learn_bonus())
						improve_points += SKILL_D(skill)->learn_bonus();
					else improve_points += 10;
// ������ʦ��ѧϰ���ܵ��ٶȣ����ض���ʦ�ĳͷ���
					improve_points = improve_points / (me->query("betrayer") + 1);
					if (improve_points < 15) improve_points = 15;
					improve_points = random(improve_points);
// ��ʦ�����ڲ������ı��ʡ�== 0ʱ����⡣
//				if(random(SKILL_D(skill)->success()) )
						me->improve_skill(skill, improve_points);
				}
				if(skill_name = SKILL_D(skill)->query_skill_name(my_skill))
	 				printf("������%s��ָ�����ԡ�%s����һ���ƺ���Щ�ĵá�\n", ob->name(), skill_name);
				else
					printf("������%s��ָ�����ƺ���Щ�ĵá�\n", ob->name());
        if (pertimes < times)
         return notify_fail("���������̫���ˣ�ѧϰ��" + chinese_number(pertimes) +"���Ժ�ֻ����ͣ������\n");
			}
			else
				return notify_fail("�����̫���ˣ����ʲôҲû��ѧ����\n");
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : learn|xue <ĳ��> <����> <����>

    ���ָ������������������й�ĳһ�ּ��ܵ��������⣬��Ȼ����
��̵Ķ�����������ϵ�����������ߣ����㾭�����ַ�ʽѧϰ����
�ļ���Ҳ�����ܸ���������̵��ˣ�Ȼ����Ϊ����ѧϰ��ʽ�൱�һ�֡�
����Ĵ��С������ѧϰ����˵����Ϥһ���¼������ķ�����

    ͨ����һ���˸�ѧ��һ���¼����ǲ�����ʲô��������ģ����Ǿ���
ʵ���ϵ�Ӧ�����������⣬��Щ������ѧϰһ���¼��ܵĹ����Ǻ���Ҫ
�ģ������Ǹ�����Ϊ�������ܻ����Ļ������ܣ�����Ҫ���ɡ��������⡪
������⡹�Ĺ��̲��ܵõ��Ϻõ�Ч��������ǽ����ַ�������Ĺ�����
��Ǳ�ܡ��Ĺ����ʾ��һ�����ܹ��Լ�����ĳЩ���⣬��ʾ���������н�
�����������Ǳ�ܣ��������������Ǳ��ʱ�Ϳ����������ָ����������
����̣�����ý�����

(PS. Ǳ�ܻ�������������Ķ��壬����ֻ������֮һ )

    ����ѧϰҲ��Ҫ����һЩ�����������ĵľ��������Լ�������ѧϰ��
��������йء�

    �������֪�����ܴӶԷ�ѧ��ʲô���ܣ�����Է������ʦ��������
�� skills ָ��ֱ�Ӳ鿴������������ʦ������ôͨ��������������ʾ��
��ֻ���Լ���취��

�������ָ�� : apprentice, practice, skills, study
HELP
	);
	return 1;
}
