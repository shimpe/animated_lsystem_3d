#include <QGuiApplication>
#include <Qt3DQuickExtras/Qt3DQuickWindow>
#include <Qt3DQuick/QQmlAspectEngine>
#include <QQmlContext>
#include "rule.h"
#include "rulesystem.h"
#include "rulesysteminterpreter.h"
#include "rulesystempresetfactory.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    RuleSystemPresetFactory f;
    LSystemPreset preset = f.createRuleSystemPreset(FIRST_SYSTEM);

    RuleSystemInterpreter ruleSystemInterpreter;
    ruleSystemInterpreter.setCalculatedString(preset.ruleSystem().calculatedString());
    ruleSystemInterpreter.setRenderHints(preset.renderHints());

    Qt3DExtras::Quick::Qt3DQuickWindow window;
    qmlRegisterUncreatableType<QQmlObjectListModelBase>("QtQmlTricks", 1, 0, "ObjectListModelBase", "ObjectListModelBase");
    window.engine()->qmlEngine()->rootContext()->setContextProperty("LSystem", &ruleSystemInterpreter);
    window.engine()->qmlEngine()->rootContext()->setContextProperty("Pipes", &ruleSystemInterpreter.getPipes());
    window.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    window.show();

    return app.exec();
}
