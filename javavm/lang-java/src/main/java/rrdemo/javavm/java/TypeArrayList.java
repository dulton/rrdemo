package rrdemo.javavm.java;

import java.util.ArrayList;
import java.util.List;

/**
 * 动态数组.
 *
 * @author zhengrr
 * @since 2016-10-26
 */
public final class TypeArrayList {
    /**
     * 构造器.
     */
    private TypeArrayList() { }

    /**
     * 声明与定义.
     */
    public static List<Character> declaringAndDefining() {
        List<Character> abc = new ArrayList<>();
        abc.add('a');
        abc.add('b');
        abc.add('c');
        return abc;
    }

    /**
     * 加入与移除.
     */
    public static void addAndRemove() {
        List<Character> bcd = declaringAndDefining();
        bcd.remove('a');
        bcd.add('d');
    }
}
