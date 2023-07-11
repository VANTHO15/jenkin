def dir_tool = "F:/Jenkin/00Source/tool_gen_eb_tresos-master"
// def zip_file = "C:/Zip/7z.exe"

pipeline {
    agent any
    stages{
        stage("Delete Output Plugin") {
            steps {
                dir("$dir_tool") {
                    script {
                       bat "rmdir /s /q Output"
                    }
                }
            }
        }
        stage("Generate Plugin") {
            steps {
                dir("$dir_tool") {
                    script {
                       bat "python main.py -m ${module}"
                    }
                }
            }
        }
        stage("Zip Plugin") {
            steps {
                script {
                    bat "${Zip_file} a ${dir_tool}/Output/${module}_HuLa.zip ${dir_tool}/Output/${module}_HuLa/*" 
                }
            }
        }
    }
}
