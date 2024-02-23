#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <functional>

class Job {
    public:
        int job_no, profit, deadline;
	Job(): job_no(0), profit(0), deadline(0) {}
        Job(int n, int p, int d): job_no(n), profit(p), deadline(d) {}
        
        friend bool operator > (const Job& a, const Job& b) {
            return a.profit > b.profit;
        }
};

class JobSlot {
    public:
        bool alloted;
        Job job;
        JobSlot(): alloted(false) {}

        void operator = (const Job& j) {
            alloted = true;
            job = j;
        }
};

class JobSequencer {
    private:
        int n, slots;
        std::vector<Job> jobs;
        std::vector<JobSlot> sel_jobs;
    public:
        JobSequencer(): slots(0) {
            std::cout << "Enter the number of jobs: ";
            std::cin >> n;

            if (n < 1)
                throw std::length_error("Cannot have length less than one.");

            for (int i = 0; i < n; i++) {
                float p, d;
                std::cout << "Enter profit and deadline of job " << i + 1 << ": ";
                std::cin >> p >> d;
                if (p < 0 || d < 0)
                    throw std::domain_error("How can profit/deadline be zero?");
                if (d > slots)
                    slots = d;
                jobs.push_back(Job(i + 1, p, d));
            }

            sel_jobs.resize(slots);
        }

        void sequence() {
            int c = 0, i = 0;
            std::sort(jobs.begin(), jobs.end(), std::greater<Job>());

            while (c < slots && i < n) {
                for (int j = jobs[i].deadline - 1; j >= 0; j--)
                    if (! sel_jobs[j].alloted) {
                        sel_jobs[j] = jobs[i];
                        c++;
			break;
                    }
               i++;
            }
        }

        void show_allotment() {
            using namespace std;
            int i = 1;
            cout << "Slot - Job - Profit" << endl;
            for (std::vector<JobSlot>::iterator slot = sel_jobs.begin(); slot != sel_jobs.end(); slot++) {
                cout << i << " - " << slot->job.job_no << " - " << slot->job.profit << endl;
                i++;
            }
        }
};

int main() {
    JobSequencer j;
    j.sequence();
    j.show_allotment();
    return 0;
}

