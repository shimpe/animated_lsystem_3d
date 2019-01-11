import QtQuick 2.9
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import Qt3D.Logic 2.0
import QtQml 2.12

Entity {
    id: sceneRoot

    property real orbitSpeed : 5.0
    property real lookSpeed: 5.0

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 5.0, -20.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    OrbitCameraController {
        id:fpc
        camera: camera
    }

    FrameAction {
        onTriggered: {
            camera.panAboutViewCenter(sceneRoot.lookSpeed * dt)
            camera.tiltAboutViewCenter(sceneRoot.orbitSpeed * dt)
        }
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                clearColor: Qt.rgba(0, 0.5, 1, 1)
                camera: camera
            }
        },
        // Event Source will be set by the Qt3DQuickWindow
        InputSettings { }
    ]


    NodeInstantiator {
        model: Pipes
        Rod {
            fromPt : LSystem.getFrom(index)
            toPt : LSystem.getTo(index)
            rad: LSystem.thickness(index)
            len: LSystem.l(index)
            w: LSystem.w(index)
            anglex: LSystem.anglex(index)
            angley: LSystem.angley(index)
            tx : LSystem.tx(index)
            ty : LSystem.ty(index)
            tz : LSystem.tz(index)
            jointExpansion : LSystem.jointExpansion(index)
            diffuseColor : LSystem.diffuseColor(index)
            specularColor : LSystem.specularColor(index)
            ambientColor : LSystem.ambientColor(index)
        }
    }

    Component.onCompleted: {
        camera.viewAll();
    }
}
