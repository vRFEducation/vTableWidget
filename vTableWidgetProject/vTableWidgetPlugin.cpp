#include "vTableWidget.h"
#include "vTableWidgetPlugin.h"

#include <QtPlugin>

vTableWidgetPlugin::vTableWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void vTableWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool vTableWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *vTableWidgetPlugin::createWidget(QWidget *parent)
{
    return new vTableWidget(parent);
}

QString vTableWidgetPlugin::name() const
{
    return QLatin1String("vTableWidget");
}

QString vTableWidgetPlugin::group() const
{
    return QLatin1String("vrfEducation Widgets");
}

QIcon vTableWidgetPlugin::icon() const
{
    return QIcon(QLatin1String(":/vTableIcon.png"));
}

QString vTableWidgetPlugin::toolTip() const
{
    return QLatin1String("A table with pagination and filtering options");
}

QString vTableWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool vTableWidgetPlugin::isContainer() const
{
    return false;
}

QString vTableWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"vTableWidget\" name=\"v_TableWidget\">\n</widget>\n");
}

QString vTableWidgetPlugin::includeFile() const
{
    return QLatin1String("vTableWidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(vTableWidgetPlugin, vTableWidgetPlugin)
#endif // QT_VERSION < 0x050000
