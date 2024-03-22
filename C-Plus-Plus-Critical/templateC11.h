#pragma once
#include <iostream>
// ��һ����Ҫ��һ��decltype�Լ�C++11ΪʲôҪ����decltype�������
// ���ȣ���C11֮ǰ(e.g. C98) ģ����Ķ��廹���Ƿǳ�����(��Ȼ����Ҳ�Ի��һ��)
// �����ģ�嶨�������һЩ����:
template<class T1, class T2>
void ft(T1 x, T2 y) {
    // ���ֳ�ʼ����ȷ��?
    T1 sum1 = x + y;
    std::cout << "sum1 is: " << sum1 << std::endl;
    T2 sum2 = x + y; 
    std::cout << "sum2 is: " << sum2 << std::endl;
}
// ֱ���������ƺ�ûʲô���⣬���ǣ����嵽����ʱ�ͻ���һЩϸ΢������
// ����:
//      ����T1��int���ͣ�T2��double���ͣ���ôx + yӦ�����Ż���double����
//      ��ôT1 sum = x + y�����ʼ�����ͻὫx + y��ֵǿ��ת����double����sum1
//      ����T1��double���ͣ�T2��float���ͣ���ôx + yӦ�����Ż���double����
//      ��ôT2 sum = x + y�����ʼ�����ͻὫx + y��ֵǿ��ת����float����sum2
//      ���ֹ���������ʱ���ܲ��������Ҳ�г��ַ�Ԥ�ڽ���Ŀ�����(�Ͼ��нضϿ���)

// ��ģ����ִ��ĳ���Ա�������淴Ӧ��������⣬����C11�Ƴ���decltype����������

// ftģ���һ����ʽ���廯
template<> void ft(int x, double y) {
    decltype(x + y) xplusy = x + y;
    std::cout << "x + y (int+double) with type decline is: " << xplusy << std::endl;
    std::cout << "type of xplusy is: " << typeid(xplusy).name() << std::endl << std::endl;
    std::cout << "The template is not used for function generation\n";
}
// ftģ�����һ����ʽ���廯
template<> void ft(double x, float y) {
    decltype(x + y) xplusy = x + y;
    std::cout << "x + y (double+float) with type decline is: " << xplusy << std::endl;
    std::cout << "type of xplusy is: " << typeid(xplusy).name() << std::endl << std::endl;
    std::cout << "The template is not used for function generation\n";
}

// �����������Ϳ����ڱ���ʱͨ��x��y���������ƶ�xplusy�����Ͳ���ָ̬��xplusy��������

// ���������ע�����������
// ������������������ʹ����void���η�����������û�з���ֵ
// ������з���ֵ�أ�
// ���ѷ���Ҳ��������������������
// �Ƿ�����������?
// template<typename T1, typename T2>
// decltype(x1+x2) ft(T1 x1, T2, x2);
// ��Ӧ�÷����������в�ͨ��
// ���������������:
// int t = x + y;
// int x=10, y=20;
// ��ᷢ��x1��x2������decltypeʹ������֮��������
// ��˱������ᱨ��
// ����ô������ֵ������������?
// C11������auto��->�Ľ��:
// �ǵģ�û��������ʽ���廯���Ͼ�����ǩ��ֻ�������ƺͲ����б�..
// template <> auto ft(double x, int y) -> decltype(x + y) {
// }
// ������������һ����confusing�����⣬����ʹ������������㴴��һ����ʽʵ�廯���������Ǳ������ᷢ��������֪�����ڴ���ģ��
// Ҳ����˵���޷�ʹ��ģ�����ɷ������Ͳ�ͬ�ĺ�������ʹ���ǵĲ����б�����ƶ���ͬ
// ���������ʽʵ����ͬ��
// template auto ft<double, int>(double x, double y) -> decltype(x + y) {
// }
// ��ʵ�������Ȼ��ģ���ǲ���������ĵģ������Ƕ����ں����������Ϣ(��������Ҳ��������)
// ��������������һ��ģ��..
// ����Ϊʲô�����һ���β�z�Ҿ���ԭ��ͦ��Ȼ�ģ���Ȼ�����԰�zȥ���������..
template<typename T1, typename T2>
auto ft(T1 x, T2 y, T2 z) -> decltype(x + y + z) {
    // �������ص�ֵ�͸�x+y+z������һ����..
    return x + y + z;
}

// ����decltype����һ������Ȥ�����ʣ�֮�����..