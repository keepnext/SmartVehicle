import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "WebSockets"
    Depends { name: "Qt"; submodules: ["core-private","websockets"]}

    architectures: ["x86_64"]
    targetPlatform: "linux"
    hasLibrary: false
    staticLibsDebug: []
    staticLibsRelease: []
    dynamicLibsDebug: []
    dynamicLibsRelease: []
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: undefined
    libNameForLinkerRelease: undefined
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: []
    cpp.includePaths: ["/home/class/Qt5.12.6/5.12.6/gcc_64/include/QtWebSockets/5.12.6","/home/class/Qt5.12.6/5.12.6/gcc_64/include/QtWebSockets/5.12.6/QtWebSockets"]
    cpp.libraryPaths: []
    
}
