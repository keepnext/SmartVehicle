import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "WebEngineCore"
    Depends { name: "Qt"; submodules: []}

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
    cpp.defines: ["QT_WEBENGINECOREHEADERS_LIB"]
    cpp.includePaths: ["/home/class/Qt5.12.6/5.12.6/gcc_64/include","/home/class/Qt5.12.6/5.12.6/gcc_64/include/QtWebEngineCore","/home/class/Qt5.12.6/5.12.6/gcc_64/include/QtWebEngineCore/5.12.6","/home/class/Qt5.12.6/5.12.6/gcc_64/include/QtWebEngineCore/5.12.6/QtWebEngineCore"]
    cpp.libraryPaths: []
    
}
