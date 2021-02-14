#include <iostream>
#include <string>
#include <map>
#include <tuple>

void DeleteEmptyTasks(TasksInfo& t) {
  TasksInfo old = t;
  for (const auto& [key, value] : old) {
    if (old[key] == 0) {
      t.erase(key);
    }
  }
}

class TeamTasks {
public:
  const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
    return PersonTasks.at(person);
  }

  void AddNewTask(const std::string& person) {
    PersonTasks[person][TaskStatus::NEW]++;
  }

  std::tuple<TasksInfo, TasksInfo> PerformPersonTasks (
						const std::string& person, int task_count) {
    TasksInfo upgrade;
    TasksInfo updated;
    TasksInfo untouched;
        auto& tasks_info = PersonTasks[person];
        for (auto& item : tasks_info) {
            if (item.first == TaskStatus::NEW) {
                if (item.second > 0) {
                    int new_status_count = item.second;
                    while (new_status_count > 0 && task_count > 0) {
                        ++updated[TaskStatus::IN_PROGRESS];
                        ++upgrade[TaskStatus::IN_PROGRESS];
                        --new_status_count;
                        --task_count;
                    }
                    if (new_status_count > 0) {
                        untouched[TaskStatus::NEW] += new_status_count;
                        upgrade[TaskStatus::NEW] += new_status_count;
                    }
                }
            }
            if (item.first == TaskStatus::IN_PROGRESS) {
                if (item.second > 0) {
                    int in_progress_status_count = item.second;
                    while (in_progress_status_count > 0 && task_count > 0) {
                        ++updated[TaskStatus::TESTING];
                        ++upgrade[TaskStatus::TESTING];
                        --in_progress_status_count;
                        --task_count;
                    }
                    if (in_progress_status_count > 0) {
                        untouched[TaskStatus::IN_PROGRESS] += in_progress_status_count;
                        upgrade[TaskStatus::IN_PROGRESS] += in_progress_status_count;
                    }
                }
            }
            if (item.first == TaskStatus::TESTING) {
                if (item.second > 0) {
                    int testing_status_count = item.second;
                    while (testing_status_count > 0 && task_count > 0) {
                        ++updated[TaskStatus::DONE];
                        ++upgrade[TaskStatus::DONE];
                        --testing_status_count;
                        --task_count;
                    }
                    if (testing_status_count > 0) {
                        untouched[TaskStatus::TESTING] += testing_status_count;
                        upgrade[TaskStatus::TESTING] += testing_status_count;
                    }
                }
            }
            if (item.first == TaskStatus::DONE) {
                if (item.second > 0) {
                    upgrade[TaskStatus::DONE] += item.second;
                }
            }
        }
        PersonTasks[person] = upgrade;
	DeleteEmptyTasks(updated);
	DeleteEmptyTasks(untouched);
        return std::make_tuple(updated, untouched);
  }
private:
    std::map<std::string, TasksInfo> PersonTasks;
};

using namespace std;

void PrintTasksInfo(const TasksInfo& tasks_info) {
    if (tasks_info.count(TaskStatus::NEW)) {
        std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
    }
    if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
        std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
    }
    if (tasks_info.count(TaskStatus::TESTING)) {
        std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
    }
    if (tasks_info.count(TaskStatus::DONE)) {
        std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
    }
}

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
    std::cout << "Updated: [";
    PrintTasksInfo(updated_tasks);
    std::cout << "] ";

    std::cout << "Untouched: [";
    PrintTasksInfo(untouched_tasks);
    std::cout << "] ";

    std::cout << std::endl;
}

int main(void) {

  TeamTasks tasks;
    TasksInfo updated_tasks;
    TasksInfo untouched_tasks;

    /* TEST 1 */
    std::cout << "Alice" << std::endl;

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
                                                                   2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
    PrintTasksInfo(updated_tasks, untouched_tasks);

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;

    /* TEST 2 */
    std::cout << "\nJack" << std::endl;

    tasks.AddNewTask("Jack");

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

    tasks.AddNewTask("Jack");

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

    tasks.AddNewTask("Jack");

    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
    std::cout << std::endl;

    /* TEST 3 */
    std::cout << "\nLisa" << std::endl;

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Lisa");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Lisa");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
    std::cout << std::endl;

    tasks.AddNewTask("Lisa");

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

    return 0;
}

/*
TasksInfo new_ti = team[person], update_tasks, old_tasks;
      int carryover = 0;
      for (const auto& [task_status, count] : team[person]) {
        if (task_count >= count && task_count != 0 && task_status != TaskStatus::DONE) {
	  if (carryover != 0) {
	    update_tasks[task_status] = carryover;
	  }
	  carryover = count;
	  new_ti[task_status] = 0;
	  task_count -= count;
	} else if (task_count < count && task_count != 0 && task_status != TaskStatus::DONE) {
	  if (carryover != 0) {
	    update_tasks[task_status] = carryover;
	    old_tasks[task_status] = count - task_count;
	    new_ti[task_status] += carryover - (count - task_count);
	    carryover = count - task_count;
	    task_count = 0;
	  } else {
	    old_tasks[task_status] = count - task_count;
	    new_ti[task_status] += carryover - task_count;
	    carryover = task_count;
	    task_count = 0;
	  }
	} else if (task_count == 0 && carryover && task_status != TaskStatus::DONE) {
	  update_tasks[task_status] = carryover;
	  break;
	} else if (carryover && task_status == TaskStatus::DONE) {
	  old_tasks[task_status] = count + carryover;
	}
      }
      team[person] = new_ti;
      return {update_tasks, old_tasks};
















------------------------------------------


TasksInfo new_ti = team[person], update_tasks, old_tasks;
      int carryover = 0;
      for (const auto& [task_status, count] : team[person]) {
        if (task_count >= count && task_count != 0 && task_status != TaskStatus::DONE) {
	  if (carryover != 0) {
	    update_tasks[task_status] = carryover;
	  }
	  carryover = count;
	  new_ti[task_status] = 0;
	  task_count -= count;
	} else if (task_count < count && task_count != 0 && task_status != TaskStatus::DONE) {
	  if (carryover != 0) {
	    update_tasks[task_status] = carryover;
	    old_tasks[task_status] = count - task_count;
	    new_ti[task_status] += carryover - (count - task_count);
	    carryover = count - task_count;
	    task_count = 0;
	  } else {
	    old_tasks[task_status] = count - task_count;
	    new_ti[task_status] += carryover - task_count;
	    carryover = task_count;
	    task_count = 0;
	  }
	} else if (task_count == 0 && carryover && task_status != TaskStatus::DONE) {
	  update_tasks[task_status] = carryover;
	  break;
	} else if (carryover && task_status == TaskStatus::DONE) {
	  old_tasks[task_status] = count + carryover;
	}
      }
      team[person] = new_ti;
      return {update_tasks, old_tasks};
 */
