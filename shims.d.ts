// Auto-generated. Do not edit.



//% color=#008B00 weight=20 icon="\uf1eb"
declare namespace infrared {

    /**
        * button pushed.
        */
    //% blockId=ir_received_left_event
    //% block="on |%btn| remotebutton pressed" shim=infrared::onPressEvent
    function onPressEvent(btn: RemoteButton, body: () => void): void;

    /**
     * initialises local variablesssss
     */
    //% blockId=IR_read block="read IR" shim=infrared::getParam
    function getParam(): int32;
}

// Auto-generated. Do not edit. Really.
