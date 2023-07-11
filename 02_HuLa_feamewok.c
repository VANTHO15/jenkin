def dir_tool = "F:/Jenkin/00Source/FW_FULL/tool"

pipeline {
    agent any
    stages{
        stage("Delete Output") {
            steps {
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
