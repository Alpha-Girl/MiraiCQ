#pragma once

class TimeTool
{
public:
	/*
	* ������˯��һ��ʱ��
	* ����`ms`��Ҫ˯�ߵ�ʱ�䣨��λ���룩,��msΪ0����Ч��msΪ1
	*/
	static void sleep(unsigned long ms)noexcept;

	/*
	* ���������غ��뼶ʱ���
	* ����ֵ�����뼶ʱ���
	*/
	static unsigned long long get_tick_count()noexcept;

private:
	TimeTool();
};

