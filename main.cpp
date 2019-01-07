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
    rs.setAxiom("FX");
    rs.addRule(Rule("X","X+YF+"));
    rs.addRule(Rule("Y","-FX-Y"));
    rs.setNoOfIterations(10);

//    rs.setAxiom("A");
//    rs.addRule(Rule("A", "B-F+CFC+F-D&F^D-F+&&CFC+F+B//"));
//    rs.addRule(Rule("B", "A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//"));
//    rs.addRule(Rule("C", "|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//"));
//    rs.addRule(Rule("D", "|CFB-F+B|FA&F^A&&FB-F+B|FC//"));
//    rs.setNoOfIterations(4);

//    rs.setAxiom("A");
//    rs.addRule(Rule("A", "[B]+[B]+[B]+[B]+[B]+[B]+[B]+[B]+[B]+[B]+[B]+[B]"));
//    rs.addRule(Rule("B", "[!X]/[!X]/[!X]/[!X]/[!X]/[!X]/[!X]/[!X]/[!X]/[!X]/[!X]/[!X]"));
//    rs.addRule(Rule("X", "[[X^!X]&!X]"));
//    rs.setNoOfIterations(4);

//    rs.setAxiom("A");
//    rs.addRule(Rule("A","X+X+X+X"));
//    rs.addRule(Rule("X","Y^A"));
//    rs.addRule(Rule("Y","A|X"));
//    rs.setNoOfIterations(4);
    RenderHints rh;
    rh.setInitialSegmentLength(1.0);
    rh.setInitialSegmentThickness(0.1);
    rh.setInitialSegmentLengthExpansion(0.5);
    rh.setInitialSegmentThicknessExpansion(0.3);

    RuleSystemInterpreter ruleSystemInterpreter;
    ruleSystemInterpreter.setAnglesInDegree(90, 90, 90);
    ruleSystemInterpreter.setCalculatedString(rs.calculatedString());
    ruleSystemInterpreter.setRenderHints(rh);

    Qt3DExtras::Quick::Qt3DQuickWindow window;
    qmlRegisterUncreatableType<QQmlObjectListModelBase>("QtQmlTricks", 1, 0, "ObjectListModelBase", "ObjectListModelBase");
    window.engine()->qmlEngine()->rootContext()->setContextProperty("LSystem", &ruleSystemInterpreter);
    window.engine()->qmlEngine()->rootContext()->setContextProperty("Pipes", &ruleSystemInterpreter.getPipes());
    window.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    window.show();

    return app.exec();
}
