#include <QGuiApplication>
#include <Qt3DQuickExtras/Qt3DQuickWindow>
#include <Qt3DQuick/QQmlAspectEngine>
#include <QQmlContext>
#include "rule.h"
#include "rulesystem.h"
#include "rulesysteminterpreter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    RuleSystem rs;
    rs.setAxiom("[X+X+X+X+X+X]-X-X-X-X-X-X");
    rs.addRule(Rule("X", "X[^X&X]-|X"));
    rs.setNoOfIterations(3);

    RuleSystemInterpreter ruleSystemInterpreter;
    ruleSystemInterpreter.setAnglesInDegree(30, 0, 0);
    ruleSystemInterpreter.setCalculatedString(rs.calculatedString());

    Qt3DExtras::Quick::Qt3DQuickWindow window;
    qmlRegisterUncreatableType<QQmlObjectListModelBase>("QtQmlTricks", 1, 0, "ObjectListModelBase", "ObjectListModelBase");
    window.engine()->qmlEngine()->rootContext()->setContextProperty("LSystem", &ruleSystemInterpreter);
    window.engine()->qmlEngine()->rootContext()->setContextProperty("Pipes", &ruleSystemInterpreter.getPipes());
    window.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    window.show();

    return app.exec();
}
