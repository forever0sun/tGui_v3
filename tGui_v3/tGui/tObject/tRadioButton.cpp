#include "tObject/tRadioButton.h"



tRadioButton::tRadioButton(int32 x, int32 y, int32 w, int32 h, const char* name) :tAbstractButton()
{
	next = this;
	selected = false;
	state = false;
	setX(x);
	setY(y);
	setW(w);
	setH(h);
	setName(name);
}


void tRadioButton::sig_depress(int32 d1, int32 d2)
{
	tPainter p;
	p.drawRadio(x(), y(), width(), height(), getName(), selected, true);
	state = true;
	callSlot((func)&tRadioButton::sig_depress,d1,d2);
}


void tRadioButton::sig_release(int32 d1, int32 d2)
{
	changeOtherSelect();
	tPainter p;
	p.drawRadio(x(), y(), width(), height(), getName(), selected, false);
	state = false;
	callSlot((func)&tRadioButton::sig_release, d1, d2);
}

void tRadioButton::release()
{
	tPainter p;
	p.drawRadio(x(), y(), width(), height(), getName(), selected, false);
	state = false;
}


void tRadioButton::show()
{
	tPainter p;
	p.drawRadio(x(), y(), width(), height(), getName(), selected, state);
}


void tRadioButton::changeOtherSelect()
{
	changeSelected();
	if (selected)//��Ϊtrue �ı����������;
	{
		tRadioButton* radio = this;
		while (radio->next != this)
		{	
			radio = radio->next;
			radio->selected = false;
			radio->show();
		}
	}
}

void tRadioButton::addNextRadio(tRadioButton* radio)
{
	radio->next = this->next;
	this->next = radio;
}

void tRadioButton::delRadio()
{
	if (this->next == this)
		return;
	tRadioButton* radio = this;
	while (radio->next != this)
		radio = radio->next;
	radio->next = this->next;
	this->next = this;
}