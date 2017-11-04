/*
 * 1. generate your trace file and teg.txt
 * 2. define your example, mainly 3 parts of it
 *      a. constructor of YourExample
 *      b. CreateRouting()
 *      c. YouRouting()
 *          note that you do can use value of s,d as index of predecessor until listS is set to be the vertex container of Graph
 * 3. run your example
 */
#include "ns3/ns3dtn-bit-helper.h"
#include "ns3/ns3dtn-bit-example-interface.h" 

using namespace ns3;

namespace ns3 {
    namespace ns3dtnbit {

        class YourExample : public DtnExampleInterface {
            public :
                YourExample(int nn, std::string method) : DtnExampleInterface() {
                    SetSchduleN(nn);
                    // simulation time should be less than trace_file_ time !Important
                    node_number_ = 12;           // change me!!
                    simulation_duration_ = 802;     // change me!!
                    print_wifi_log_ = false;
                    if (method == "Spray") {
                        ex_rm_ = DtnApp::RoutingMethod::SprayAndWait;
                    } else if (method == "Heuristic") {
                        ex_rm_ = DtnApp::RoutingMethod::Other;
                    } else if (method == "TEG") {
                        ex_rm_ = DtnApp::RoutingMethod::TimeExpanded;
                    } else if (method == "CGR") {
                        ex_rm_ = DtnApp::RoutingMethod::CGR;
                    } else {
                        std::cerr << "can't find routing method name or don't assign one." << std::endl;
                        abort();
                    }

                    {
                        // assign node_number_ and simulation_duration_ by different schdule_for_n_trace
                        if (schdule_for_n_trace == 6) {
                            node_number_ = 20;
                            simulation_duration_ = 802;
                        } else if (schdule_for_n_trace == 4) {
                            node_number_ = 15;
                            simulation_duration_ = 802;
                        } else if (schdule_for_n_trace == 8) {
                            node_number_ = 15;
                            simulation_duration_ = 802;
                                                                 // name in graph
                        } else if (schdule_for_n_trace == 101    // cycle-traffic1
                                || schdule_for_n_trace == 102    // cycle-traffic2
                                || schdule_for_n_trace == 103    // cycle-traffic3
                                || schdule_for_n_trace == 104    // cycle-traffic4
                                || schdule_for_n_trace == 105    // cycle-traffic5
                                || schdule_for_n_trace == 106    // cycle-traffic6
                                || schdule_for_n_trace == 107    // cycle-traffic7
                                || schdule_for_n_trace == 108    // cycle-traffic8
                                || schdule_for_n_trace == 109    // cycle-traffic9
                                || schdule_for_n_trace == 110    // cycle-traffic10
                                || schdule_for_n_trace == 111    // cycle-traffic11
                                || schdule_for_n_trace == 112    // cycle-traffic12
                                || schdule_for_n_trace == 113    // cycle-traffic13
                                || schdule_for_n_trace == 114    // cycle-traffic14
                                || schdule_for_n_trace == 115    // cycle-traffic15
                                || schdule_for_n_trace == 116    // cycle-traffic16
                                || schdule_for_n_trace == 117    // cycle-traffic17
                                || schdule_for_n_trace == 118    // cycle-traffic18
                                || schdule_for_n_trace == 119    // cycle-traffic19
                                || schdule_for_n_trace == 120    // cycle-traffic20
                                || schdule_for_n_trace == 121    // cycle-traffic21
                                || schdule_for_n_trace == 122    // cycle-traffic22
                                || schdule_for_n_trace == 123    // cycle-traffic23
                                ) { 
                                    // 0100_current_trace.tcl + 0100_teg.txt
                            node_number_ = 12;
                            simulation_duration_ = 802;
                                                                 // name in graph
                        } else if (schdule_for_n_trace == 201    // tx1-traffic1
                                || schdule_for_n_trace == 202
                                || schdule_for_n_trace == 203
                                || schdule_for_n_trace == 204
                                || schdule_for_n_trace == 205
                                || schdule_for_n_trace == 206
                                || schdule_for_n_trace == 207
                                || schdule_for_n_trace == 208
                                || schdule_for_n_trace == 209
                                || schdule_for_n_trace == 210
                                || schdule_for_n_trace == 211
                                || schdule_for_n_trace == 212
                                || schdule_for_n_trace == 213
                                || schdule_for_n_trace == 214
                                || schdule_for_n_trace == 215
                                || schdule_for_n_trace == 216
                                ) { 
                                    // 0200_current_trace.tcl + 0200_teg.txt
                            node_number_ = 7;
                            simulation_duration_ = 1000;
                        } else if (schdule_for_n_trace == 301    // ra1-traffic1
                                || schdule_for_n_trace == 302
                                || schdule_for_n_trace == 303
                                || schdule_for_n_trace == 304
                                || schdule_for_n_trace == 305
                                || schdule_for_n_trace == 306
                                || schdule_for_n_trace == 307
                                || schdule_for_n_trace == 308
                                || schdule_for_n_trace == 309
                                || schdule_for_n_trace == 310
                                || schdule_for_n_trace == 311
                                || schdule_for_n_trace == 312
                                || schdule_for_n_trace == 313
                                || schdule_for_n_trace == 314
                                || schdule_for_n_trace == 315
                                || schdule_for_n_trace == 316
                                ) { 
                                    // 0200_current_trace.tcl + 0200_teg.txt
                            node_number_ = 6;
                            simulation_duration_ = 1000;
                        } else {

                            cout << "warn: " << __FILE__ << __LINE__ << endl;
                            std::abort();
                        }
                    }

                }
                void ReportEx(std::ostream& os) override {
                    os << "Here In DtnExampleInterface::ReportEx" 
                        << "BundleTrace:node_number_=" << node_number_ 
                        << ";simulation_duration_=" << simulation_duration_ << endl;
                }

                void ScheduleTask() override {
                    int sch_size = 345;
                    /*
                    auto handy_func = [sch_size, this](double sch_time, int dstnode, int i) {
                        std::cout << "bundle send schedule: time=" << sch_time << ";node-" << i << "send " << sch_size << " size-pkt to node-" << dstnode << std::endl;
                        this->apps_[i]->ScheduleTx(Seconds(sch_time), dstnode, sch_size);
                    };
                    */
                    auto handy_func_x = [sch_size, this](double sch_time, int dstnode, int i, int times) {
                        for (double rt = sch_time; rt < sch_time + times * 10; rt += 10.0) {
                            std::cout << "bundle send schedule: time=" << rt << ";node-" << i << "send " << sch_size << " size-pkt to node-" << dstnode << std::endl;
                            this->apps_[i]->ScheduleTx(Seconds(rt), dstnode, sch_size);
                        }
                    };
                    {
                        // Schedule differently by schdule_for_n_trace
                        // following code is just handy used, not essential, you can do it yourself
                        if (schdule_for_n_trace > 100) {
                            std::srand(std::time(0));
                            auto amount = schdule_for_n_trace % 100;
                            while (amount --) {
                                if (schdule_for_n_trace > 300) {
                                    int rand1 = std::rand() % 6;
                                    int rand2 = std::rand() % 6;
                                    int rand3 = std::rand() % 6;
                                    while (rand1 == rand2) {rand2 = std::rand() % 6;}
                                    while (rand2 == rand3 || rand1 == rand3) {rand3 = std::rand() % 6;}
                                    handy_func_x(100 + amount * 17, rand1, rand2, 17);
                                    handy_func_x(100 + amount * 17, rand2, rand3, 17);
                                    handy_func_x(100 + amount * 17, rand3, rand1, 17);
                                } else if (schdule_for_n_trace > 200) {
                                    handy_func_x(100 + amount * 12, 5, 6, 35);
                                    handy_func_x(300 + amount * 15, 6, 5, 35);
                                } else if (schdule_for_n_trace > 100) {
                                    handy_func_x(200 + amount * 20, 4, 10, 6);
                                    handy_func_x(100 + amount * 20, 0, 10, 7);
                                } else {
                                    abort();
                                }
                            }
                        } else if (schdule_for_n_trace == 6) {
                            // moving group
                            DtnExampleInterface::ScheduleTask();
                        } else if (schdule_for_n_trace == 4) {
                            // random
                            DtnExampleInterface::ScheduleTask();
                        } else if (schdule_for_n_trace == 8) {
                            // random-2
                            DtnExampleInterface::ScheduleTask();
                        } else {
                            cout << "WARN: can't find schdule, define it or use default random one " << endl;
                            std::abort();
                        }
                    }
                }

                void SetSchduleN(size_t n) override {
                    assert(n != 0);
                    schdule_for_n_trace = n;
                    set_th(schdule_for_n_trace);
                }

            private :
                size_t schdule_for_n_trace = 0; // the number of example you are running, different example number may have different packet schedule and node moving
        };

    } /* ns3dtnbit */ 

} /* ns3  */ 

int main(int argc, char *argv[]) {
    //!important LOG control
    LogComponentEnable ("DtnRunningLog",LOG_LEVEL_DEBUG);
    //LogComponentEnable ("DtnRunningLog",LOG_LEVEL_INFO);
    //LogComponentEnable ("DtnRunningLog",LOG_LEVEL_LOGIC);
    //LogComponentEnable ("DtnRunningLog", LOG_LEVEL_ALL);
    LogComponentEnable("Ns2MobilityHelper", LOG_LEVEL_INFO);
    //LogComponentEnable("UdpSocket", LOG_LEVEL_INFO);
    //LogComponentEnable("UdpL4Protocol", LOG_LEVEL_INFO);

    assert(std::is_move_constructible<ns3dtnbit::YourExample>::value);
    assert(std::is_move_assignable<ns3dtnbit::YourExample>::value);
    int n = 102;  // the number of YourExample you are running
    std::string sss = "Spray";

    if (argc == 1) {
        std::cout << "please give some argument to identify the example number you want to run. If you were building this, let it go and remenber to run the excutable with argument." << std::endl;
        //std::abort();
    } else {
        auto ss = std::string(argv[1]);
        sss = std::string(argv[2]);
        n = stoi(ss);
        std::cout << "example number is '" << n << "'" << std::endl;
    }
    std::unique_ptr<ns3dtnbit::DtnExampleInterface> exp(new ns3dtnbit::YourExample(n, sss));
    auto runner = ns3dtnbit::DtnExampleRunner();
    runner.RunnerLoad(exp).RunIt(argc, argv);
    return 0;
}
