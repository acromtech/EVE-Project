public enum FrameType {
    TX_FRAME(0x10),
    RX_FRAME(0x20);
    
    private final int value;

    FrameType(int value) {
        this.value = value;
    }
    public int getValue() {
        return value;
    }
}
