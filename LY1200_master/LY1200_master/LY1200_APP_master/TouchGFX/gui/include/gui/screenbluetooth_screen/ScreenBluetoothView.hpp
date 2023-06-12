#ifndef SCREENBLUETOOTHVIEW_HPP
#define SCREENBLUETOOTHVIEW_HPP

#include <gui_generated/screenbluetooth_screen/ScreenBluetoothViewBase.hpp>
#include <gui/screenbluetooth_screen/ScreenBluetoothPresenter.hpp>
extern uint8_t MenuLevel ;//全局变量 此层=2 第三层
class ScreenBluetoothView : public ScreenBluetoothViewBase
{
public:
    ScreenBluetoothView();
    virtual ~ScreenBluetoothView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t);
protected:
};

#endif // SCREENBLUETOOTHVIEW_HPP
