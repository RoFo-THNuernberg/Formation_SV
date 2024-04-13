import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: "../../.."

    ofApp {
        name: { return FileInfo.baseName(sourceDirectory) }

        files: [
            '../../../../../../../opt/ros/noetic/share/catkin/cmake/toplevel.cmake',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/data_logger/CMakeLists.txt',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/data_logger/package.xml',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/data_logger/src/data_logger.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/formation_controller/CMakeLists.txt',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/formation_controller/package.xml',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/CMakeLists.txt',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/include/ros_bridge_server/CommunicationHandler.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/include/ros_bridge_server/Publisher.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/include/ros_bridge_server/RosMsgs.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/include/ros_bridge_server/Socket.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/include/ros_bridge_server/Subscriber.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/include/ros_bridge_server/msg_id.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/package.xml',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/src/CommunicationHandler.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/src/RosMsgs.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/src/Socket.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/ros_bridge_server/src/ros_bridge_server.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/rviz_msg_transformer/CMakeLists.txt',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/rviz_msg_transformer/package.xml',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/rviz_msg_transformer/rviz/rviz_config.rviz',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/rviz_msg_transformer/src/rviz_msg_transformer.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/CMakeLists.txt',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/msg/c_trajec.msg',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/msg/c_trajec_vector.msg',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/package.xml',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/circletrajectory.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/circletrajectory.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/crsplinetrajectory.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/crsplinetrajectory.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/csplinetrajectory.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/csplinetrajectory.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/gnuplot-iostream.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/main.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/pos_d.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/spline.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/spline.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/test.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/trajechandler.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/trajechandler.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/trajecmaster.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/trajecmaster.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/trajectorobot.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/trajectorobot.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/trajectory.cpp',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/src/trajectory.h',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/srv/addCSplineTrajecHandler.srv',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/srv/addCircleTrajecHandler.srv',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/srv/addCrSplineTrajecHandler.srv',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/srv/boolRequest.srv',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/srv/float32Request.srv',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/srv/plotTrajecXoY.srv',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/srv/plotTrajectory.srv',
            '../../../../Doesch_RoboterFormation/Roboterformation_ROS/src/trajecgenerator/srv/removeTrajecHandler.srv',
            'src/main.cpp',
            'src/ofApp.cpp',
            'src/ofApp.h',
        ]

        of.addons: [
            'ofxGui',
            'ofxOpenCv',
            'ofxOsc',
            'ofxTuio',
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
                                // and can be checked with #ifdef or #if in the code
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.staticLibraries: []  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
                                // will compile OF only once for all your projects
                                // otherwise compiled per project with qbs
    

    property bool precompileOfMain: false  // precompile ofMain.h
                                           // faster to recompile when including ofMain.h 
                                           // but might use a lot of space per project

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
