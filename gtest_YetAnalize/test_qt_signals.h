#ifndef TEST_QT_SIGNALS_H
#define TEST_QT_SIGNALS_H

// require: QT += testlib

/* example of using:
    SignalArgCatcher<bool> my_signal_spy(my_object, SIGNAL(signal_func(bool)));
    my_signal_spy.setExpected_emission_index(0);
    my_signal_spy.setExpected_emission_arg_index(0);
    .. or ..
    SignalArgCatcher<bool, 0, 0> my_signal_spy(my_object, SIGNAL(signal_func(bool)));
    ... activity with sending signals ...
    EXPECT_TRUE(my_signal_spy.getCapturedArg());
*/

#include <QSignalSpy>
#include <QVariant>

class TestSignal : public QSignalSpy
{
public:
    TestSignal(const QObject *obj, const char *aSignal)
        : QSignalSpy(obj, aSignal)
    {
        signal_repr = &aSignal[1];
        TestSignal *connected_signal = this;
        EXPECT_TRUE(connected_signal->isValid())
                << "check signal signature: "
                << qUtf8Printable(signal_repr);
    }

    QVariant getSignalArgValue(int indexOfEmission, int indexOfArgument)
    {
        bool isSignalEmissionAlreadyHappend =
                (indexOfEmission < count());
        EXPECT_TRUE(isSignalEmissionAlreadyHappend)
                << "when work with signal: "
                << qUtf8Printable(signal_repr)
                << "; requested index of emission = " << indexOfEmission
                << ", count of all emissions = " << count();

        if (!isSignalEmissionAlreadyHappend)
        {
            return QVariant();
        }

        QList<QVariant> emitted_signal_vals =
                this->at(indexOfEmission);

        bool isSignalArgumentExist =
                (indexOfArgument < emitted_signal_vals.size());
        EXPECT_TRUE(isSignalArgumentExist)
                << "when work with signal: "
                << qUtf8Printable(signal_repr)
                << "; requested index of arg = " << indexOfArgument
                << ", count of all arguments = " << emitted_signal_vals.size();

        if (!isSignalArgumentExist)
        {
            return QVariant();
        }

        return (emitted_signal_vals.at(indexOfArgument));
    }

    QVariant getSignalArgValueAndClear(int indexOfEmission, int indexOfArgument)
    {
        QVariant val = getSignalArgValue(indexOfEmission,
                                         indexOfArgument);
        clear();
        return val;
    }

    QString signal_repr;
};

template <typename TypeOfTestingArg,
          int expected_emission_index = 0, // номер посылки сигнала
          int expected_emission_arg_index = 0> // номер аргумента сигнала
class SignalArgCatcher : public TestSignal
{
public:
    SignalArgCatcher(const QObject *obj, const char *aSignal)
        : TestSignal(obj, aSignal)
    {
        setExpected_emission_index(expected_emission_index);
        setExpected_emission_arg_index(expected_emission_arg_index);
    }

    TypeOfTestingArg getCapturedArg()
    {
        return getCapturedArg(getExpected_emission_index(),
                              getExpected_emission_arg_index(),
                              true);
    }

    TypeOfTestingArg getCapturedArg(int emission_index,
                                    int arg_index,
                                    bool isClearAfterAll = false)
    {
        QVariant capturedArgumentValue;

        if (isClearAfterAll)
        {
            capturedArgumentValue = getSignalArgValueAndClear(
                                emission_index,
                                arg_index);
        }
        else
        {
            capturedArgumentValue = getSignalArgValue(
                                emission_index,
                                arg_index);
        }

        TypeOfTestingArg valForReturn = TypeOfTestingArg();

        EXPECT_TRUE(capturedArgumentValue.isValid())
                << "when work with signal: "
                << qUtf8Printable(signal_repr);

        if (capturedArgumentValue.isValid())
        {
            EXPECT_TRUE(capturedArgumentValue.canConvert<TypeOfTestingArg>())
                    << "when work with signal: "
                    << qUtf8Printable(signal_repr);

            valForReturn = capturedArgumentValue.value<TypeOfTestingArg>();
        }

        return valForReturn;
    }


    int getExpected_emission_index() const
    {
        return expected_emission_index_;
    }

    void setExpected_emission_index(int index)
    {
        expected_emission_index_ = index;
    }

    int getExpected_emission_arg_index() const
    {
        return expected_emission_arg_index_;
    }

    void setExpected_emission_arg_index(int index)
    {
        expected_emission_arg_index_ = index;
    }

private:
    int expected_emission_index_ = 0;
    int expected_emission_arg_index_ = 0;
};


#endif // TEST_QT_SIGNALS_H
