def dir_tool = "F:/Jenkin/00Source/FW_FULL/tool"
def dir_tool_output = "F:/Jenkin/00Source/FW_FULL/output/${module}"

pipeline {
    agent any
    stages{
        stage("Replace File and Delete Output") {
            steps {
                script {
                    def user_config = readFile(file: "${dir_tool}/UserConfig_Template.py")
                    user_config = user_config.replace("MODULE_REPLACE","${module}")
                    user_config = user_config.replace("TEST_NAME_REPLACE","${test_name}")
                    user_config = user_config.replace("COMPILER_REPLACE","${compiler}")
                    user_config = user_config.replace("DEBUGER_REPLACE","${debuger}")
                    writeFile(file: "${dir_tool}/UserConfig.py", text: user_config)
                    println("DONE REPLACE")
                }
                dir("$dir_tool") {
                    script {
                       bat "python main.py -o clean"
                    }
                }
            }
        }
        
        stage("Generate Plugin") {
            steps {
                dir("$dir_tool") {
                    script {
                    //   bat "python main.py -o generate"
                        echo "Waiting License"
                    }
                }
            }
        }
        stage("Compile Code") {
            steps {
                dir("$dir_tool") {
                    script {
                       bat "python main.py -o compile"
                    }
                }
            }
        }
        stage("Run Code and Report") {
            steps {
                dir("$dir_tool") {
                    script {
                       bat "python main.py -o nodebug"
                       bat "python main.py -o report"
                    }
                }
            }
        }
        stage("Export Report") {
            steps {
                dir("dir_tool_output") {
                    script {
                       bat "${Zip_file} a ${dir_tool}/../output/${module}/${test_name}/${compiler}.zip ${dir_tool}/../output/${module}/${test_name}/${compiler}/*" 
                       archiveArtifacts artifacts: "${test_name}/${compiler}.zip", fingerprint: true
                    }
                }
            }
        }
    }
}
