#!/bin/bash

getDate() {
  date +"%d/%m/%Y"
}

heading="Summary of $(getDate):"
ending="CHECKOUT"

tasksWithProject=()

echo
echo "Enter the task list, type 'E' to terminate and 'C' to change the project name."
echo

terminate=false

while [ "$terminate" = false ]; do
  read -p "Enter the Project Name: " projectName
  echo

  if [ "$projectName" == "E" ]; then
    break
  fi

  tasks=()
  
  while true; do
    read -p "Enter Task: " task
    if [ "$task" == "E" ]; then
      terminate=true
      break
    elif [ "$task" == "C" ]; then
      break
    fi
    tasks+=("$task")
  done

  tasksWithProject+=("$projectName" "${tasks[@]}")
done

if [ ${#tasksWithProject[@]} -gt 0 ]; then
  echo "Generating..."
  echo
  echo "$heading"
  echo

  for ((i = 0; i < ${#tasksWithProject[@]}; i += 2)); do
    project="${tasksWithProject[i]}"
    tasks=("${tasksWithProject[i + 1]}")

    echo "$project"
    for task in "${tasks[@]}"; do
      echo "COMPLETED $task"
    done

    if [ $i -lt $(( ${#tasksWithProject[@]} - 2 )) ]; then
      echo
    fi
  done

  echo
  echo "$ending"
fi
