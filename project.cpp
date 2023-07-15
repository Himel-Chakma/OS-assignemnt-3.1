#include<bits/stdc++.h>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int waiting_time;
    int turnaround_time;
    int end_time;
    int response_time;
    int remainingTime;
    int priority;

    void initialize(){
        remainingTime = burst_time;
    }
};


bool compare(Process a, Process b) {
    return a.arrival_time < b.arrival_time;
}

void FCFS(Process p[], int n, bool comp) {

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
    }

    sort(p, p + n, compare);

    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time > current_time) {
            current_time = p[i].arrival_time;
        }
        p[i].start_time = current_time;
        p[i].waiting_time = current_time - p[i].arrival_time;
        p[i].response_time = p[i].waiting_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        p[i].end_time = current_time + p[i].burst_time;
        current_time += p[i].burst_time;
    }
    double total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0, avg_waiting_time = 0, avg_turnaround_time = 0, avg_response_time;
    if(comp)
    {
        for (int i = 0; i < n; i++) {
            total_waiting_time += p[i].waiting_time;
            total_turnaround_time += p[i].turnaround_time;
            total_response_time += p[i].response_time;
        }

        avg_waiting_time = total_waiting_time / n;
        avg_turnaround_time = total_turnaround_time / n;
        avg_response_time = total_response_time / n;

        cout<<"Algo: FCFS\t\t";
        cout << "Average response time: " << avg_response_time <<"\t";
        cout << "Average waiting time: " << avg_waiting_time <<"\t";
        cout << "Average turnaround time: " << avg_turnaround_time << endl;
    }
    else
    {
    cout<<"Grantt Chart:\n";
    for(int i = 0; i < n; i++) {
        cout<<p[i].start_time<<" P"<<p[i].pid <<" ";
    }
    cout<<"\n";

    cout << "Process Information\n";
    for (int i = 0; i < n; i++) {
        cout << "Process: P" << p[i].pid
             << " Start time: " << p[i].waiting_time
             << " End time: " << p[i].end_time
             << " Waiting time: " << p[i].waiting_time
             << " Turnaround time: " << p[i].turnaround_time
             << " Response time: " << p[i].response_time
             << endl;
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
        total_response_time += p[i].response_time;
    }

    avg_waiting_time = total_waiting_time / n;
    avg_turnaround_time = total_turnaround_time / n;
    avg_response_time = total_response_time / n;

    cout << "Average response time: " << avg_response_time << endl;
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
    }
}

void SJF(Process p[], int n, bool comp) {

    for(int i = 0; i < n; i++) {

        p[i].pid = i + 1;

    }

    sort(p, p + n, compare);

    int current_time = 0;

    for(int i = 0; i < n; i++) {
        int shortest_burst = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].arrival_time <= current_time && p[j].burst_time < p[shortest_burst].burst_time) {
                shortest_burst = j;
            }
        }
        swap(p[i], p[shortest_burst]);
        p[i].start_time = current_time;
        p[i].waiting_time = current_time - p[i].arrival_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        p[i].end_time = current_time + p[i].burst_time;
        p[i].response_time = p[i].waiting_time;
        current_time += p[i].burst_time;
    }

    float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;
    if(comp)
    {
        for(int i = 0; i < n; i++) {
            total_waiting_time += p[i].waiting_time;
            total_turnaround_time += p[i].turnaround_time;
            total_response_time += p[i].response_time;
        }
        cout << "Algo: SJF\t\t";
        cout << "Average response time: " << total_response_time/ n << "\t";
        cout << "Average waiting time: " << total_waiting_time / n << "\t\t";
        cout << "Average turnaround time: " << total_turnaround_time / n << endl;
    }
    else
    {
    cout << "Gantt Chart:\n";
    for(int i = 0; i < n; i++) {
        cout << p[i].start_time << " P" << p[i].pid << " ";
    }
    cout << "\n";
    for (int i = 0; i < n; ++i) {
        cout << "Process: P" << i + 1 << " Start time: " << p[i].start_time << " End time: " << p[i].end_time
             << " Waiting time: " << p[i].waiting_time << " Turnaround time: " << p[i].turnaround_time
             << " Response time: " << p[i].response_time << endl;
    }

    for(int i = 0; i < n; i++) {
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
        total_response_time += p[i].response_time;
    }

    cout << "Average response time: " << total_response_time/ n << endl;
    cout << "Average waiting time: " << total_waiting_time / n << endl;
    cout << "Average turnaround time: " << total_turnaround_time / n << endl;
    }

}

void SJFP(int a[], int b[], int n, bool comp) {

    int st[n],pp[n],ct[n],bb[n],tat[n],wt[n],rt[n];
    for(int i = 0; i < n ; i++){
        bb[i]=b[i];
        st[i]=-1;
        pp[i]=-1;
    }
    priority_queue<pair<int,pair<int,int> >>pq;
    int t=0;
    vector<int>v,sst,enn;

    while(1){
         int mn=-1;
         for(int i = 0; i < n ; i++){
              if(a[i]<=t){
                  if(pp[i]==-1){
                      pq.push({-b[i],{-a[i],i}});
                      pp[i]=1;
                  }
              }
              else{
                 if(mn==-1){
                    mn=a[i];
                 }
                 else{
                    mn=min(mn,a[i]);
                 }
              }
         }

         if(pq.size()==0&&mn==-1)break;
         if(pq.size()==0){
              t=mn;
         }
         else{
            pair<int,pair<int,int>>pr=pq.top();
            pq.pop();
            int in=pr.second.second;
            if(st[in]==-1)st[in]=t;
            sst.push_back(t);
            b[in]--;
            t++;
            v.push_back(in);
            enn.push_back(t);
            if(b[in]!=0){
                pq.push({-b[in],{-a[in],in}});
            }
            else{
                ct[in]=t;
            }
         }
    }
    while(!pq.empty()){
            pair<int,pair<int,int>>pr=pq.top();
            pq.pop();
            int in=pr.second.second;
            sst.push_back(t);
            t+=b[in];
            v.push_back(in);
            enn.push_back(t);
            ct[in]=t;
    }
     double atat=0,awt=0,art=0;
    if(comp)
    {

     for(int i = 0; i < n ; i++){
        tat[i]=ct[i]-a[i];
        wt[i]=tat[i]-bb[i];
        rt[i]=st[i]-a[i];
        atat+=tat[i];
        awt+=wt[i];
        art+=rt[i];
     }
     atat/=n;
     awt/=n;
     art/=n;
        cout<<"Algo: SJFP\t\t";
     cout<<"Average Response Time: "<<art<<"\t";
     cout<<"Average Waiting Time: "<<awt<<"\t";
     cout<<"Average Turnaround Time: "<<atat<<endl;

    }
    else
    {
    cout<<"Gantt Chart"<<endl;
    int ss=0,en;
    t=0;
    cout<<t;
    for(int i = 0; i < v.size() ; i++){
         if(i==0){
            ss=sst[i];
            en=enn[i];
         }
         else{
              if(v[i]==v[i-1]){
                  en=enn[i];
              }
              else{

                  if(ss>t){
                     cout<<" idle "<< ss;
                  }
                  cout<<" P"<<v[i-1]+1<<" "<<en;
                  ct[v[i-1]]=en;
                  t=en;
                  ss=sst[i];
                  en=enn[i];
              }
         }
    }


     if(ss>t){
        cout<<" idle "<< ss;
     }
     cout<<" P"<<v[v.size()-1]+1<<" "<<en;
     cout<<endl;
     ct[v[v.size()-1]]=en;
     for(int i = 0; i < n ; i++){
        tat[i]=ct[i]-a[i];
        wt[i]=tat[i]-bb[i];
        rt[i]=st[i]-a[i];
        atat+=tat[i];
        awt+=wt[i];
        art+=rt[i];
     }
     atat/=n;
     awt/=n;
     art/=n;

     for(int i = 0; i < n ; i++){
        cout<<"Process:P"<<i+1<<" Start time: "<<st[i];
        cout<<" End time: "<<ct[i];
        cout<<" Response time: "<<rt[i];
        cout<<" Waiting time: "<<wt[i];
        cout<<" Turnaround time: "<<tat[i]<<endl;
     }
     cout<<"Average Response Time: "<<art<<endl;
     cout<<"Average Waiting Time: "<<awt<<endl;
     cout<<"Average Turnaround Time: "<<atat<<endl;
    }

}

void NPP(int arr[], int burst[], int pri[], int n, bool compr) {

     int burst1[n];
     int fist=INT_MAX,id;
    for( int i=0;i<n;i++){
        burst1[i]=burst[i];
        if(arr[i]<fist){
            fist=arr[i];
            id=i+1;
        }
    }
    vector< int>gc,tc;
    if(fist!=0){
        tc.push_back(0);
        gc.push_back(-1);
        tc.push_back(fist);
    }
    else tc.push_back(fist);
     int vis[n+1]={0};
    vis[id]=1;
     int cnt=n;
    while(1){
        if(!cnt) break;
        gc.push_back(id);
        fist+=burst[id-1];
        tc.push_back(fist);
        cnt--;
        vis[id]=1;
        if(!cnt) break;
        int c=INT_MAX,d,e=INT_MAX,f,g=INT_MAX,h=INT_MAX;
        for( int i=0;i<n;i++){
            if(vis[i+1]) continue;
            if(arr[i]<=fist){
                if(pri[i]<c){
                    c=pri[i];d=i;
                }
                else if(pri[i]==c){
                    if(burst[i]<burst[d]){
                        d=i;
                    }
                    else if(burst[i]==burst[d]){
                        if(arr[i]<arr[d]){
                            d=i;
                        }
                    }
                }
            }
            if(arr[i]<e) e=arr[i],f=i+1;
        }
        if(c==INT_MAX){
            tc.push_back(e);
            gc.push_back(-1);
            fist=e;id=f;
        }
        else{
            id=d+1;
        }
    }
    if(compr)
    {
     int comp[n+1]={0},start[n+1];
    for( int i=1;i<tc.size();i++){
        comp[gc[i-1]]=tc[i];
        start[gc[i-1]]=tc[i-1];
    }
     int tat[n+1]={0},wait[n+1]={0},resp[n+1]={0};
    double atat=0.0,await=0.0,aresp=0.0;
    for( int i=1;i<=n;i++){
        tat[i]=comp[i]-arr[i-1];
        wait[i]=tat[i]-burst1[i-1];
        resp[i]=start[i]-arr[i-1];
        atat+=tat[i]*1.0;
        await+=wait[i]*1.0;
        aresp+=resp[i]*1.0;
    }
    cout<<"Algo: NPP\t\t";
    cout<<"Average Response Time: "<<aresp/(n*1.0)<<"\t";
    cout<<"Average Waiting Time: "<<await/(n*1.0)<<"\t\t";
    cout<<"Average Turnaround Time: "<<atat/(n*1.0)<<endl;
    }
    else
    {
    cout<<"Gantt Chart:"<<endl;
    cout<<tc[0]<<" ";
     int comp[n+1]={0},start[n+1];
    for( int i=1;i<tc.size();i++){
        if(gc[i-1]==-1) cout<<"Idle ";
        else cout<<"P"<<gc[i-1]<<" ";
        cout<<tc[i]<<" ";
        comp[gc[i-1]]=tc[i];
        start[gc[i-1]]=tc[i-1];
    }
    cout<<endl;
     int tat[n+1]={0},wait[n+1]={0},resp[n+1]={0};
    double atat=0.0,await=0.0,aresp=0.0;
    for( int i=1;i<=n;i++){
        tat[i]=comp[i]-arr[i-1];
        wait[i]=tat[i]-burst1[i-1];
        resp[i]=start[i]-arr[i-1];
        atat+=tat[i]*1.0;
        await+=wait[i]*1.0;
        aresp+=resp[i]*1.0;
    }
    for( int i=1;i<=n;i++){
        cout<<"Process: P"<<i<<" "<<"Start time: "<<start[i]<<" "<<"End time: "<<comp[i]<<" "<<"Response Time: "<<resp[i]<<" "<<"Waiting time: "<<wait[i]<<" "<<"Turnaround time: "<<tat[i]<<endl;
    }
    cout<<"Average Response Time: "<<aresp/(n*1.0)<<endl;
    cout<<"Average Waiting Time: "<<await/(n*1.0)<<endl;
    cout<<"Average Turnaround Time: "<<atat/(n*1.0)<<endl;
    }
}

void PP(Process processes[], int m, bool comp) {

    for (int n = 0; n < m; n++) {
        processes[n].pid = n + 1;

        processes[n].initialize();
    }

    for (int i = 0; i < m - 1; i++) {
        for (int j = i + 1; j < m; j++) {
            if (processes[j].arrival_time < processes[i].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[i];
                processes[i] = temp;
            }
        }
    }
    if(comp)
    {
    int currentTime = processes[0].arrival_time;

    while (true) {
        int currentHighestPriorityIndex = -1;
        int currentHighestPriority = numeric_limits<int>::max();
        bool isAllCompleted = true;

        for (int i = 0; i < m; i++) {
            if (processes[i].remainingTime > 0) {
                isAllCompleted = false;
                if (processes[i].arrival_time <= currentTime) {
                    if (processes[i].priority < currentHighestPriority) {
                        currentHighestPriority = processes[i].priority;
                        currentHighestPriorityIndex = i;
                    }
                }
            }
        }

        if (isAllCompleted) {
            break;
        }

        if (processes[currentHighestPriorityIndex].remainingTime == processes[currentHighestPriorityIndex].burst_time) {
            processes[currentHighestPriorityIndex].response_time = currentTime;
        }

        processes[currentHighestPriorityIndex].remainingTime--;
        currentTime++;

        if (processes[currentHighestPriorityIndex].remainingTime == 0) {
            processes[currentHighestPriorityIndex].end_time = currentTime;
        }
    }

    int sumresponse_time = 0;
    int sumend_time = 0;
    int sumwaiting_time = 0;
    int sumturnaround_time = 0;


    for (int n = 0; n < m; n++) {
        processes[n].turnaround_time = processes[n].end_time - processes[n].arrival_time;
        processes[n].waiting_time = processes[n].turnaround_time - processes[n].burst_time;
        sumresponse_time += processes[n].response_time;
        sumend_time += processes[n].end_time;
        sumwaiting_time += processes[n].waiting_time;
        sumturnaround_time += processes[n].turnaround_time;
    }
    cout << "Algo: P Priority\t";
    cout << "Average Response Time: " << (float)sumresponse_time / m <<"\t";
    cout << "Average Waiting Time: " << (float)sumwaiting_time / m <<"\t";
    cout << "Average Turn Around Time: " << (float)sumturnaround_time / m << endl;
    }
    else
    {
        cout << "Gantt Chart:\n";
    int currentTime = processes[0].arrival_time;

    while (true) {
        int currentHighestPriorityIndex = -1;
        int currentHighestPriority = numeric_limits<int>::max();
        bool isAllCompleted = true;

        for (int i = 0; i < m; i++) {
            if (processes[i].remainingTime > 0) {
                isAllCompleted = false;
                if (processes[i].arrival_time <= currentTime) {
                    if (processes[i].priority < currentHighestPriority) {
                        currentHighestPriority = processes[i].priority;
                        currentHighestPriorityIndex = i;
                    }
                }
            }
        }

        if (isAllCompleted) {
            break;
        }

        if (processes[currentHighestPriorityIndex].remainingTime == processes[currentHighestPriorityIndex].burst_time) {
            processes[currentHighestPriorityIndex].response_time = currentTime;
        }

        cout << currentTime << " P" << processes[currentHighestPriorityIndex].pid << " ";

        processes[currentHighestPriorityIndex].remainingTime--;
        currentTime++;

        if (processes[currentHighestPriorityIndex].remainingTime == 0) {
            processes[currentHighestPriorityIndex].end_time = currentTime;
        }
    }

    cout << endl;

    int sumresponse_time = 0;
    int sumend_time = 0;
    int sumwaiting_time = 0;
    int sumturnaround_time = 0;

    cout << endl;

    for (int n = 0; n < m; n++) {
        cout << "Process " << processes[n].pid << ":";
        cout << " Response Time: " << processes[n].response_time;
        processes[n].turnaround_time = processes[n].end_time - processes[n].arrival_time;
        processes[n].waiting_time = processes[n].turnaround_time - processes[n].burst_time;
        cout << " Waiting Time: " << processes[n].waiting_time;
        cout << " Turn Around Time: " << processes[n].turnaround_time << endl;

        sumresponse_time += processes[n].response_time;
        sumend_time += processes[n].end_time;
        sumwaiting_time += processes[n].waiting_time;
        sumturnaround_time += processes[n].turnaround_time;
    }

    cout << "\nAverage Response Time: " << (float)sumresponse_time / m;
    cout << "\nAverage Waiting Time: " << (float)sumwaiting_time / m;
    cout << "\nAverage Turn Around Time: " << (float)sumturnaround_time / m;
    }
}

void RR(Process prc[], int n, int timeQuantum, bool comp) {
    int i, j, time, remainingprc, flag = 0;
    float avgwt = 0, avgtat = 0;

    int totalburst_time = 0;
    remainingprc = n;

    for (i = 0; i < n; i++) {
        prc[i].pid = i;
        prc[i].remainingTime = prc[i].burst_time;
        totalburst_time += prc[i].burst_time;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (prc[i].arrival_time > prc[j].arrival_time) {
                swap(prc[i], prc[j]);
            }
        }
    }

    if(comp)
    {
    vector<int> start_time(n + 1, 0);

    for (time = 0, i = 0; remainingprc != 0;) {
        if (prc[i].remainingTime <= timeQuantum && prc[i].remainingTime > 0) {
            time += prc[i].remainingTime;
            if (start_time[prc[i].pid] == 0) {
                start_time[prc[i].pid] = time;
            }

            prc[i].remainingTime = 0;
            flag = 1;
        } else if (prc[i].remainingTime > 0) {
            prc[i].remainingTime -= timeQuantum;
            time += timeQuantum;
            if (start_time[prc[i].pid] == 0) {
                start_time[prc[i].pid] = time;
            }
        }
        if (prc[i].remainingTime == 0 && flag == 1) {
            remainingprc--;
            prc[i].turnaround_time = time - prc[i].arrival_time;
            prc[i].waiting_time = time - prc[i].arrival_time - prc[i].burst_time;
            avgwt += time - prc[i].arrival_time - prc[i].burst_time;
            avgtat += time - prc[i].arrival_time;
            flag = 0;
        }
        if (i == n - 1)
            i = 0;
        else if (prc[i + 1].arrival_time <= time)
            i++;
        else
            i = 0;
    }

    double avgrt = 0;
    for (i = 0; i < n; i++) {
        avgrt += (start_time[prc[i].pid] - prc[i].arrival_time);
    }

    avgwt = avgwt / n;
    avgrt /= n;
    avgtat = avgtat / n;
    cout << "Algo: Round Robin\t";
    cout << "Average Response Time: " << avgrt << "\t";
    cout << "Average Waiting Time: " << avgwt << "\t";
    cout << "Average Turnaround Time: " << avgtat << endl;
    }
    else
    {
    cout << "Gantt Chart" << endl;

    vector<int> start_time(n + 1, 0);

    cout << "0 ";
    for (time = 0, i = 0; remainingprc != 0;) {
        if (prc[i].remainingTime <= timeQuantum && prc[i].remainingTime > 0) {
            time += prc[i].remainingTime;
            if (start_time[prc[i].pid] == 0) {
                start_time[prc[i].pid] = time;
            }
            cout << "P" << prc[i].pid + 1 << " ";
            if (time != totalburst_time) {
                cout << time << " ";
            }

            prc[i].remainingTime = 0;
            flag = 1;
        } else if (prc[i].remainingTime > 0) {
            prc[i].remainingTime -= timeQuantum;
            time += timeQuantum;
            if (start_time[prc[i].pid] == 0) {
                start_time[prc[i].pid] = time;
            }
            cout << "P" << prc[i].pid + 1 << " ";
            if (time != totalburst_time) {
                cout << time << " ";
            }
        }
        if (prc[i].remainingTime == 0 && flag == 1) {
            remainingprc--;
            prc[i].turnaround_time = time - prc[i].arrival_time;
            prc[i].waiting_time = time - prc[i].arrival_time - prc[i].burst_time;
            avgwt += time - prc[i].arrival_time - prc[i].burst_time;
            avgtat += time - prc[i].arrival_time;
            flag = 0;
        }
        if (i == n - 1)
            i = 0;
        else if (prc[i + 1].arrival_time <= time)
            i++;
        else
            i = 0;
    }
    cout << endl;

    double avgrt = 0;
    for (i = 0; i < n; i++) {
        cout << "Process: " << prc[i].pid + 1 << " Start Time: " << start_time[prc[i].pid]
             << " Waiting Time: " << prc[i].waiting_time << " Turnaround Time: " << prc[i].turnaround_time
             << " Response Time: " << start_time[prc[i].pid] - prc[i].arrival_time << endl;
        avgrt += (start_time[prc[i].pid] - prc[i].arrival_time);
    }

    avgwt = avgwt / n;
    avgrt /= n;
    avgtat = avgtat / n;
    cout << "Average Response Time: " << avgrt << endl;
    cout << "Average Waiting Time: " << avgwt << endl;
    cout << "Average Turnaround Time: " << avgtat << endl;
    }

}

void ownalgo(Process processes[], int n, bool comp) {
    int i, j, time, remainingProcesses, flag = 0;

    float avgwaiting_time = 0, avgturnaround_time = 0;

    int totalburst_time = 0;
    remainingProcesses = n;

    for (i = 0; i < n; i++) {
        processes[i].pid = i;
        processes[i].remainingTime = processes[i].burst_time;
        totalburst_time += processes[i].burst_time;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                swap(processes[i], processes[j]);
            }
        }
    }

    int meanburst_time = totalburst_time / n;
    int lowestburst_time = INT_MAX;
    for (i = 0; i < n; i++) {
        if (processes[i].burst_time < lowestburst_time) {
            lowestburst_time = processes[i].burst_time;
        }
    }

    int timeQuantum = sqrt(meanburst_time * lowestburst_time);

    if(comp)
    {

    vector<int> timeline(n + 1, 0);

    for (time = 0, i = 0; remainingProcesses != 0;) {
        if (processes[i].remainingTime <= timeQuantum && processes[i].remainingTime > 0) {
            time += processes[i].remainingTime;
            if (timeline[processes[i].pid] == 0) {
                timeline[processes[i].pid] = time;
            }

            processes[i].remainingTime = 0;
            flag = 1;
        } else if (processes[i].remainingTime > 0) {
            processes[i].remainingTime -= timeQuantum;
            time += timeQuantum;
            if (timeline[processes[i].pid] == 0) {
                timeline[processes[i].pid] = time;
            }
        }
        if (processes[i].remainingTime == 0 && flag == 1) {
            remainingProcesses--;
            processes[i].turnaround_time = time - processes[i].arrival_time;
            processes[i].waiting_time = time - processes[i].arrival_time - processes[i].burst_time;
            avgwaiting_time += time - processes[i].arrival_time - processes[i].burst_time;
            avgturnaround_time += time - processes[i].arrival_time;
            flag = 0;
        }
        if (i == n - 1)
            i = 0;
        else if (processes[i + 1].arrival_time <= time)
            i++;
        else
            i = 0;
    }

    double avgResponseTime = 0;
    for (i = 0; i < n; i++) {
        avgResponseTime += (timeline[processes[i].pid] - processes[i].arrival_time);
    }

    avgwaiting_time = avgwaiting_time / n;
    avgResponseTime /= n;
    avgturnaround_time = avgturnaround_time / n;
    cout << "Algo: Own\t\t";
    cout << "Average Response Time: " << avgResponseTime << "\t";
    cout << "Average Waiting Time: " << avgwaiting_time << "\t";
    cout << "Average Turnaround Time: " << avgturnaround_time << endl;
    }
    else
    {
    cout << "Gantt Chart" << endl;

    vector<int> timeline(n + 1, 0);

    cout << "0 ";
    for (time = 0, i = 0; remainingProcesses != 0;) {
        if (processes[i].remainingTime <= timeQuantum && processes[i].remainingTime > 0) {
            time += processes[i].remainingTime;
            if (timeline[processes[i].pid] == 0) {
                timeline[processes[i].pid] = time;
            }
            cout << "P" << processes[i].pid + 1 << " ";
            if (time != totalburst_time) {
                cout << time << " ";
            }

            processes[i].remainingTime = 0;
            flag = 1;
        } else if (processes[i].remainingTime > 0) {
            processes[i].remainingTime -= timeQuantum;
            time += timeQuantum;
            if (timeline[processes[i].pid] == 0) {
                timeline[processes[i].pid] = time;
            }
            cout << "P" << processes[i].pid + 1 << " ";
            if (time != totalburst_time) {
                cout << time << " ";
            }
        }
        if (processes[i].remainingTime == 0 && flag == 1) {
            remainingProcesses--;
            processes[i].turnaround_time = time - processes[i].arrival_time;
            processes[i].waiting_time = time - processes[i].arrival_time - processes[i].burst_time;
            avgwaiting_time += time - processes[i].arrival_time - processes[i].burst_time;
            avgturnaround_time += time - processes[i].arrival_time;
            flag = 0;
        }
        if (i == n - 1)
            i = 0;
        else if (processes[i + 1].arrival_time <= time)
            i++;
        else
            i = 0;
    }
    cout << endl;

    double avgResponseTime = 0;
    for (i = 0; i < n; i++) {
        cout << "Process: " << processes[i].pid + 1 << " Start Time: " << timeline[processes[i].pid]
             << " Waiting Time: " << processes[i].waiting_time << " Turnaround Time: " << processes[i].turnaround_time
             << " Response Time: " << timeline[processes[i].pid] - processes[i].arrival_time << endl;
        avgResponseTime += (timeline[processes[i].pid] - processes[i].arrival_time);
    }

    avgwaiting_time = avgwaiting_time / n;
    avgResponseTime /= n;
    avgturnaround_time = avgturnaround_time / n;
    cout << "Average Waiting Time: " << avgwaiting_time << endl;
    cout << "Average Turnaround Time: " << avgturnaround_time << endl;
    cout << "Average Response Time: " << avgResponseTime << endl;
    }

}

int main() {

    int n, timeQuantum;

    int a[100], b[100], p[100], a1[100], b1[100], p1[100];

    bool comp = false;

    Process processes[10];

    int choice;
    cout << "1: FCFS" << endl;
    cout << "2: Non-Preemptive-SJF" << endl;
    cout << "3: Preemptive-SJF" << endl;
    cout << "4: Non-Preemptive-Priority" << endl;
    cout << "5: Preemptive-Priority" << endl;
    cout << "6: Round-Robin" << endl;
    cout << "7: Your-Own-Algorithm" << endl;
    cout << "8: Compare-All" << endl;
    cout << "9: Exit" << endl;
    cout << "Input your choice: ";
    cin>>choice;

    if(choice == 8)
    {
        comp = true;
    }

    switch(choice) {
    case 1:
    case 2:
    case 3:
        cout << "Enter the number of processes: ";
        cin >> n;

        for(int i = 0; i < n; i++) {
            cout << "Enter the burst time of P" << i + 1 << ": ";
            cin >> b[i];
            cout << "Enter the arrival time of P" << i + 1 << ": ";
            cin >> a[i];
        }

        for(int i = 0; i < n; i++) {
            processes[i].burst_time = b[i];
            processes[i].arrival_time = a[i];
            processes[i].pid = i + 1;
        }
        if(choice == 1) {
            FCFS(processes, n, comp);
        }
        if(choice == 2) {
            SJF(processes, n, comp);
        }
        if(choice == 3) {
            SJFP(a, b, n, comp);
        }
        break;
    case 4:
    case 5:
        cout << "Enter the number of processes: ";
        cin >> n;

        for(int i = 0; i < n; i++) {
            cout << "Enter the burst time of P" << i + 1 << ": ";
            cin >> b[i];
            cout << "Enter the arrival time of P" << i + 1 << ": ";
            cin >> a[i];
            cout << "Enter the priority of P" << i + 1 << ": ";
            cin >> p[i];
        }
        for(int i = 0; i < n; i++) {
            processes[i].burst_time = b[i];
            processes[i].arrival_time = a[i];
            processes[i].priority = p[i];
            processes[i].pid = i + 1;
        }
        if(choice == 4) {
            NPP(a, b, p, n, comp);
        }
        if(choice == 5) {
            PP(processes, n, comp);
        }
        break;
    case 6:
        cout << "Enter the number of processes: ";
        cin >> n;

        for(int i = 0; i < n; i++) {
            cout << "Enter the burst time of P" << i + 1 << ": ";
            cin >> b[i];
            cout << "Enter the arrival time of P" << i + 1 << ": ";
            cin >> a[i];
        }

        for(int i = 0; i < n; i++) {
            processes[i].burst_time = b[i];
            processes[i].arrival_time = a[i];
        }
        cout << "Enter the time quantum: ";
        cin >> timeQuantum;
        RR(processes, n, timeQuantum, comp);
        break;
    case 7:
        cout << "Enter the number of processes: ";
        cin >> n;

        for(int i = 0; i < n; i++) {
            cout << "Enter the burst time of P" << i + 1 << ": ";
            cin >> b[i];
            cout << "Enter the arrival time of P" << i + 1 << ": ";
            cin >> a[i];
        }

        for(int i = 0; i < n; i++) {
            processes[i].burst_time = b[i];
            processes[i].arrival_time = a[i];
        }
        ownalgo(processes, n, comp);
        break;
    case 8:
        cout << "Enter the number of processes: ";
        cin >> n;

        for(int i = 0; i < n; i++) {
            cout << "Enter the burst time of P" << i + 1 << ": ";
            cin >> b[i];
            b1[i] = b[i];
            cout << "Enter the arrival time of P" << i + 1 << ": ";
            cin >> a[i];
            a1[i] = a[i];
            cout << "Enter the priority of P" << i + 1 << ": ";
            cin >> p[i];
            p1[i] = p[i];
        }
        cout << "Enter the time quantum: ";
        cin >> timeQuantum;
        for(int i = 0; i < n; i++) {
            processes[i].burst_time = b[i];
            processes[i].arrival_time = a[i];
            processes[i].pid = i + 1;
        }
        FCFS(processes, n, comp);
        SJF(processes, n, comp);
        SJFP(a, b, n, comp);
        NPP(a1, b1, p1, n, comp);
        PP(processes, n, comp);
        RR(processes, n, timeQuantum, comp);
        ownalgo(processes, n, comp);
        break;
    }
}
