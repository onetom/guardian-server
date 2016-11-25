================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : CPUViewer Project Overview
===============================================================================

The application wizard has created this CPUViewer application for 
you.  This application not only demonstrates the basics of using the Microsoft 
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your CPUViewer application.

CPUViewer.vcproj
    This is the main project file for VC++ projects generated using an application wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    application wizard.

CPUViewer.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CCPUViewerApp application class.

CPUViewer.cpp
    This is the main application source file that contains the application
    class CCPUViewerApp.

CPUViewer.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\CPUViewer.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file CPUViewer.rc.

res\CPUViewer.rc2
    This file contains resources that are not edited by Microsoft 
    Visual C++. You should place all resources not editable by
    the resource editor in this file.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:
    Windows Explorer Style: The project will include a Windows Explorer-like
    interface, with two frames.

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

LeftView.h, LeftView.cpp
    These files contain the left frame class CLeftView, which is derived from
    CTreeView.

/////////////////////////////////////////////////////////////////////////////

The application wizard creates one document type and one view:

CPUViewerDoc.h, CPUViewerDoc.cpp - the document
    These files contain your CCPUViewerDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CCPUViewerDoc::Serialize).

CPUViewerView.h, CPUViewerView.cpp - the view of the document
    These files contain your CCPUViewerView class.
    CCPUViewerView objects are used to view CCPUViewerDoc objects.





/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named CPUViewer.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, you will need 
to redistribute the MFC DLLs. If your application is in a language 
other than the operating system's locale, you will also have to 
redistribute the corresponding localized resources MFC80XXX.DLL. 
For more information on both of these topics, please see the section on 
redistributing Visual C++ applications in MSDN documentation. 

/////////////////////////////////////////////////////////////////////////////
