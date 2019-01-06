import QtQuick 2.9
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import QtQml 2.12

Entity {
    id: rod
    property vector3d fromPt : Qt.vector3d(0,0,0)
    property vector3d toPt : Qt.vector3d(1,0,0)
    property real rad: 0.1
    property real len: 1
    property real w: 1
    property real anglex: 0
    property real angley: 0
    property real tx : 0
    property real ty : 0
    property real tz : 0
    property color diffuseColor : "white"
    property color specularColor : "white"
    property color ambientColor : "gold"

    Entity {
        id: corner1
        PhongMaterial {
            id: sphereMaterial
            diffuse: diffuseColor
            specular: specularColor
            ambient: ambientColor
        }

        SphereMesh {
            id: sphereMesh
            radius: rad
            rings: 20
            slices: 20

            Transform {
                id: sphereTransform
                scale: 1.0
                translation: {
                    var from = fromPt
                    //console.log("from ", from)
                    Qt.vector3d(from.x,from.y,from.z)
                }
            }
        }

        components: [ sphereMesh, sphereMaterial, sphereTransform ]
    }

    Entity {
        id: corner2
        PhongMaterial {
            id: sphereMaterial2
            diffuse: diffuseColor
            specular: specularColor
            ambient: ambientColor
        }

        SphereMesh {
            id: sphereMesh2
            radius: rad
            rings: 20
            slices: 20

            Transform {
                id: sphereTransform2
                scale: 1.0
                translation: {
                    var to = toPt
                    //console.log("to ", to);
                    Qt.vector3d(to.x,to.y,to.z)
                }
            }
        }

        components: [ sphereMesh2, sphereMaterial2, sphereTransform2 ]
    }


    Entity {
        id: cylinderEntity

        PhongMaterial {
            id: material
            diffuse: diffuseColor
            specular: specularColor
            ambient: ambientColor
        }

        CylinderMesh {
            id: cylinderMesh
            radius: {
                //console.log("thickness ", LSystem.thickness(index))
                rad
            }
            length: {
                //console.log("l ", LSystem.l(index))
                len
            }
            rings: 2
            slices: 20

            Transform {
                id: cylinderTransform

                scale: 1.0

                rotation: {
                    var Qvx = Qt.vector3d(1, 0, 0)
                    var Qvy = Qt.vector3d(0, (w<0)?-1:1, 0)
                    //console.log("index ", index);
                    //console.log("angleX ", LSystem.anglex(index), "angleY ", LSystem.angley(index));
                    fromAxesAndAngles(Qvx, anglex, Qvy, angley)
                }

                translation: {
                    //console.log("tx ", LSystem.tx(index), " ty ", LSystem.ty(index), " tz ", LSystem.tx(index))
                    Qt.vector3d(tx, ty, tz)
                }
            }
        }

        components: [ cylinderMesh, material, cylinderTransform ]
    }
}

