﻿#include <ZUI.h>

rb_root *Global_ControlClass;
void ZuiCoreInit(void *data) {
	((ZCtlProc)data)(Proc_CoreInit, NULL, NULL, NULL, NULL, NULL);
}
BOOL ZuiControlRegister()
{
	Global_ControlClass = rb_new();
	/*核心组件 不可卸载*/
	ZuiControlRegisterAdd(L"layout", (ZCtlProc)&ZuiLayoutProc);
	ZuiControlRegisterAdd(L"verticallayout", (ZCtlProc)&ZuiVerticalLayoutProc);
	ZuiControlRegisterAdd(L"horizontallayout", (ZCtlProc)&ZuiHorizontalLayoutProc);
	ZuiControlRegisterAdd(L"tablayout", (ZCtlProc)&ZuiTabLayoutProc);
	ZuiControlRegisterAdd(L"tilelayout", (ZCtlProc)&ZuiTileLayoutProc);

	ZuiControlRegisterAdd(L"window", (ZCtlProc)&ZuiWindowProc);
	ZuiControlRegisterAdd(L"button", (ZCtlProc)&ZuiButtonProc);
	ZuiControlRegisterAdd(L"browser", (ZCtlProc)&ZuiBrowserProc);

	/*初始化全部控件*/
	rb_foreach(Global_ControlClass, ZuiCoreInit);
	return TRUE;
}
ZEXPORT ZuiBool ZCALL ZuiControlRegisterAdd(ZuiText *name, ZCtlProc Proc)
{
	return rb_insert((key_t)Zui_Hash(name), Proc, Global_ControlClass);
}
ZEXPORT ZuiBool ZCALL ZuiControlRegisterDel(ZuiText *name)
{
	rb_delete((key_t)Zui_Hash(name), Global_ControlClass);
	return 0;
}
