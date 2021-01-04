//ENGINE EVENT

    engine_ignite(); //ignite the e-match

    engine_stop();

    engine_fail();

//INIT SEQUENCE

    init_sensors();
    init_actuators();
    init_sd();
    init_modem();
    init_buffer(); //init the buffer

//Acquisition event

    data_send(); //send datas to RFD900
    data_save(); //save datas
    data_fetch(); //triggered by the RFD900

    data_start();
    data_stop();

//TRIGGER EVENT

    main_pressure_trigger();
    second_pressure_trigger();
    main_temp_trigger();
    