enum Id {
    JAVA(0x01),
    C(0x02);
    
    private final int value;
    
    Id(int value) {
        this.value = value;
    }
    
    public int getValue() {
        return value;
    }
}
