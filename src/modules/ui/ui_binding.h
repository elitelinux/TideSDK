/**
 * Copyright (c) 2012 - 2014 TideSDK contributors
 * http://www.tidesdk.org
 * Includes modified sources under the Apache 2 License
 * Copyright (c) 2008 - 2012 Appcelerator Inc
 * Refer to LICENSE for details of distribution and use.
 **/

#ifndef _UI_BINDING_H_
#define _UI_BINDING_H_

#include <tide/tide.h>
#include "menu_item.h"
#include "notification.h"

namespace ti
{
    class UIBinding : public AccessorObject
    {

    public:
        UIBinding(Host *host);
        virtual ~UIBinding();
        Host* GetHost();

        void CreateMainWindow(AutoPtr<WindowConfig> config);
        AutoUserWindow GetMainWindow();
        std::vector<AutoUserWindow>& GetOpenWindows();
        void AddToOpenWindows(AutoUserWindow);
        void RemoveFromOpenWindows(AutoUserWindow);
        void ClearTray();
        void UnregisterTrayItem(TrayItem*);
        void _GetOpenWindows(const ValueList& args, ValueRef result);
        void _GetMainWindow(const ValueList& args, ValueRef result);
        void _CreateWindow(const ValueList& args, ValueRef result);
        void _CreateNotification(const ValueList& args, ValueRef result);
        void _CreateMenu(const ValueList& args, ValueRef result);
        void _CreateMenuItem(const ValueList& args, ValueRef result);
        void _CreateCheckMenuItem(const ValueList& args, ValueRef result);
        void _CreateSeparatorMenuItem(const ValueList& args, ValueRef result);
        AutoMenu __CreateMenu(const ValueList& args);
        AutoMenuItem __CreateMenuItem(const ValueList& args);
        AutoMenuItem __CreateCheckMenuItem(const ValueList& args);
        AutoMenuItem __CreateSeparatorMenuItem(const ValueList& args);
        void _SetMenu(const ValueList& args, ValueRef result);
        void _GetMenu(const ValueList& args, ValueRef result);
        void _SetContextMenu(const ValueList& args, ValueRef result);
        void _GetContextMenu(const ValueList& args, ValueRef result);
        void _SetIcon(const ValueList& args, ValueRef result);
        void _SetIcon(std::string iconURL);
        void _AddTray(const ValueList& args, ValueRef result);
        void _ClearTray(const ValueList& args, ValueRef result);
        void _GetIdleTime(const ValueList& args, ValueRef result);

        /* OS X specific callbacks */
        void _SetDockIcon(const ValueList& args, ValueRef result);
        void _SetDockMenu(const ValueList& args, ValueRef result);
        void _SetBadge(const ValueList& args, ValueRef result);
        void _SetBadgeImage(const ValueList& args, ValueRef result);

        virtual AutoMenu CreateMenu() = 0;
        virtual AutoMenuItem CreateMenuItem() = 0;;
        virtual AutoMenuItem CreateCheckMenuItem() = 0;
        virtual AutoMenuItem CreateSeparatorMenuItem() = 0;
        virtual void SetMenu(AutoMenu) = 0;
        virtual void SetContextMenu(AutoMenu) = 0;
        virtual void SetIcon(std::string& iconPath) = 0;
        virtual AutoTrayItem AddTray(std::string& iconPath, TiMethodRef cbSingleClick) = 0;
        virtual AutoMenu GetMenu() = 0;
        virtual AutoMenu GetContextMenu() = 0;
        virtual long GetIdleTime() = 0;

        /* These have empty impls, because are OS X-only for now */
        virtual void SetDockIcon(std::string& icon_path) {}
        virtual void SetDockMenu(AutoMenu) {}
        virtual void SetBadge(std::string& badgeLabel) {}
        virtual void SetBadgeImage(std::string& badgeImagePath) {}

        static void ErrorDialog(std::string);
        static inline UIBinding* GetInstance() { return instance; }

    protected:
        static UIBinding* instance;
        Host* host;
        AutoUserWindow mainWindow;
        std::vector<AutoUserWindow> openWindows;
        std::vector<AutoTrayItem> trayItems;
        std::string iconURL;

        static void Log(Logger::Level level, std::string& message);
    };
}

#endif
