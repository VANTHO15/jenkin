def dir_tool = "F:/Jenkin/00Source/FW_FULL/tool"

pipeline {
    agent any
    stages{
        stage("Replace File and Delete Output") {
            steps {
                script {
                    def user_config = readFile(file: "${dir_tool}/UserConfig_Template.py")
                    user_config = user_config.replace("MODULE_REPLACE","${module}")
                    println(user_config)
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
        stage("Run Code") {
            steps {
                dir("$dir_tool") {
                    script {
                       bat "python main.py -o nodebug"
                    }
                }
            }
        }
        stage("Export Report") {
            steps {
                dir("$dir_tool") {
                    script {
                       bat "python main.py -o report"
                    }
                }
            }
        }
        
    }
}
