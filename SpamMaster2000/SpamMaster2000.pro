TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

LIBS	+= -lm -lpthread -lccext -lxml2 -ldl -lccgnu

HEADERS	+= abook.h \
	compare.h \
	contact.h \
	mail.h \
	mailbox.h \
	mailboxes.h \
	pop.h \
	prefs.h \
	smtp.h
SOURCES	+= abook.cpp \
	compare.cpp \
	contact.cpp \
	mail.cpp \
	mailbox.cpp \
	mailboxes.cpp \
	main.cpp \
	pop.cpp \
	prefs.cpp \
	smtp.cpp
FORMS	= abookform.ui \
	addcontact.ui \
	mainWindow.ui \
	newmailboxdialog.ui \
	savemail.ui \
	sendmailform.ui
IMAGES	= images/editcopy \
	images/editcut \
	images/editpaste \
	images/filenew \
	images/fileopen \
	images/filesave \
	images/print \
	images/redo \
	images/redstar.png \
	images/searchfind \
	images/stalin_klar.jpg \
	images/undo \
	images/stalin_2.jpg











































































































































































































































































































































unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}


