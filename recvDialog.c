// created by: geo (April 2012)
#include "recvDialog.h"


void recvDialog_Create(XtPointer xt_List, struct Broadcast_Packet* p_Item)
{
	Widget* w_List = (Widget*)xt_List;
	
	Widget RECVDIALOG_Dialog;
	Widget RECVDIALOG_Panel;
	Widget RECVDIALOG_Form;
	Widget RECVDIALOG_Frame;
	Widget RECVDIALOG_LblG_FrameTitle;
	Widget RECVDIALOG_LblG_FrameChild;	
	Widget RECVDIALOG_Text_Message;
	Widget RECVDIALOG_BtnG_Reply;
	
	char str_Buff[150];	
	XmString xstr_Buff;
	
	int mCount;
	int mIdx = 0;
	XmStringTable xstr_list;
	char* text;	
	
	// Get the current entries (and number of entries) from the List
	XtVaGetValues (*w_List, XmNitemCount, &mCount,	XmNitems, &xstr_list, NULL);

	while(mCount>mIdx)
	{		
		text = (char *) XmStringUnparse (xstr_list[mIdx], NULL,XmCHARSET_TEXT, XmCHARSET_TEXT,NULL, 0, XmOUTPUT_ALL);
		
		if (strstr(text, p_Item->IP_Address) != '\0')
		{
			// str_Item comes before item
			sprintf(str_Buff, "%s\n%s", text, asctime(localtime ((const time_t *)&p_Item->UNIX_Time)));
			XtFree(text);
			break;
		}		
		
		XtFree(text);						
		mIdx++;
	}	
	
	
		
	// Create dialog
	n = 0;
	XtSetArg (args[n], XmNtitle, "Recieve Message"); n++;
	XtSetArg (args[n], XmNdeleteResponse, XmDESTROY); n++;
	XtSetArg (args[n], XmNdefaultPosition, False); n++;
	XtSetArg (args[n], XmNx, posX); n++;
	XtSetArg (args[n], XmNy, posY); n++;
	RECVDIALOG_Dialog = (Widget) XmCreateDialogShell (XtParent (*w_List), "recv_diag", args, n);
		
	posX += 20;
	posY += 20;
		
	// Create paned window
	RECVDIALOG_Panel = XmCreatePanedWindow (RECVDIALOG_Dialog, "recv_panel", NULL, 0);
		
	// Create form
	RECVDIALOG_Form = XmCreateForm (RECVDIALOG_Panel, "recv_form", NULL, 0);
	
	
	// Create frame
	n = 0;
	XtSetArg (args[n], XmNshadowType, XmSHADOW_ETCHED_OUT); n++;
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	XtSetArg (args[n], XmNleftOffset, 5); n++;
	XtSetArg (args[n], XmNrightOffset, 5); n++;
	RECVDIALOG_Frame = XmCreateFrame (RECVDIALOG_Form, "recv_frame", args, n);
	
	
	// Create handle field
	xstr_Buff = XmStringCreateLocalized (str_Buff);
		
	n = 0;
	XtSetArg (args[n], XmNchildType, XmFRAME_WORKAREA_CHILD); n++;
	XtSetArg (args[n], XmNlabelString, xstr_Buff); n++;
	RECVDIALOG_LblG_FrameChild = XmCreateLabelGadget (RECVDIALOG_Frame, "recv_frame_child", args, n);
	XtManageChild (RECVDIALOG_LblG_FrameChild);		
	
	
	// Create frame title
	n = 0;
	XtSetArg (args[n], XmNchildType, XmFRAME_TITLE_CHILD); n++;
	XtSetArg (args[n], XmNchildVerticalAlignment, XmALIGNMENT_CENTER); n++;
	RECVDIALOG_LblG_FrameTitle = XmCreateLabelGadget (RECVDIALOG_Frame, "Message from", args, n);	
	XtManageChild (RECVDIALOG_LblG_FrameTitle);	
	
	XtManageChild (RECVDIALOG_Frame);
	
	// Create reply button
	n = 0;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	RECVDIALOG_BtnG_Reply = XmCreatePushButtonGadget (RECVDIALOG_Form, "Reply", args, n);		
	XtAddCallback (RECVDIALOG_BtnG_Reply, XmNactivateCallback, recvDialog_ReplyCallBack, RECVDIALOG_Dialog);
	XtManageChild (RECVDIALOG_BtnG_Reply);

	
	// Creatr text message
	n = 0;
	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++; 												
	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;	
	XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++; 
	XtSetArg (args[n], XmNtopWidget, RECVDIALOG_Frame); n++;
	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_WIDGET); n++;	
	XtSetArg (args[n], XmNbottomWidget, RECVDIALOG_BtnG_Reply); n++;
	XtSetArg (args[n], XmNleftOffset, 5); n++;
	XtSetArg (args[n], XmNtopOffset, 5); n++;
	XtSetArg (args[n], XmNrightOffset, 5); n++;
	XtSetArg (args[n], XmNbottomOffset, 5); n++;
	
	XtSetArg (args[n], XmNrows, 10); n++;
	XtSetArg (args[n], XmNcolumns, 50); n++;
	XtSetArg (args[n], XmNscrollHorizontal, False); n++;
	XtSetArg (args[n], XmNwordWrap, True); n++;
	XtSetArg (args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
	XtSetArg (args[n], XmNeditable, False); n++;
	XtSetArg (args[n], XmNcursorPositionVisible, False); n++;
	XtSetArg (args[n], XmNvalue, p_Item->Handlename); n++;
	RECVDIALOG_Text_Message = XmCreateScrolledText(RECVDIALOG_Form, "Message", args, n);	
	XtManageChild (RECVDIALOG_Text_Message);	
		
	XtManageChild (RECVDIALOG_Form);
	XtManageChild (RECVDIALOG_Panel);
	XtManageChild (RECVDIALOG_Dialog);
	
	XmStringFree (xstr_Buff);
}


void recvDialog_ReplyCallBack(Widget widget, XtPointer client_data, XtPointer call_data)
{
	Widget* SENDDIALOG_Dialog = (Widget*)client_data;
	//Widget* SENDDIALOG_List_Users = (Widget*)client_data+1;
	//Widget* SENDDIALOG_Text_Message = (Widget*)client_data+2;
	

//	sendDialog_Create(client_data, 2);
	
	
//	appIcon_ReplyDialog(1);
	
	XtDestroyWidget(*SENDDIALOG_Dialog);	
	appIcon_ReplyDialog(1);	
}

