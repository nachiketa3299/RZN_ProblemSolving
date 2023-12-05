/*!
* @file BOJ_1717_231205.cpp
* @date 2023-12-05T10:29 11:30 ���� 50�� �ɸ�
* ���� 1717 ������ ǥ�� G5
* 2��, 128MB
*/

/*!
* �ʱ⿡ \f$n+1\f$ �� ���� \f$\{0\}, \{1\}, ..., \{n\}\f$�� �ִ�.
* ���⿡ ������ �����, �� ���Ұ� ���� ���տ� ���ԵǾ� �ִ��� Ȯ���ϴ� ������ �����Ϸ��� �Ѵ�.
* ������ ǥ���ϴ� ���α׷��� �ۼ��Ѵ�.
*/

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>

#ifdef PS_DEBUG
#include <string>
#endif

using namespace std;

/// Type Alias
using CountType = size_t;
using OperandType = size_t;
using IndexType = size_t;

/*!
* @enum Operation
* @brief ������ ������ ��Ÿ���� ������
*/
enum Operation 
{ 
    Union = 0,  //< ������ ����(0)
    Membership  //< ���� ���θ� Ȯ���ϴ� ����(1)
};

/// @struct Command
/// @short ��ɾ�� �����ڸ� �����ϴ� ����ü
struct Command
{
    Command(const Operation& opcode, const OperandType& op1, const OperandType op2): opcode(opcode), op1(op1), op2(op2) {};

    /// @short ������ ����
    Operation opcode;
    /// @short �ǿ����� 1
    OperandType op1;
    /// @short �ǿ����� 2
    OperandType op2;

#ifdef PS_DEBUG
    string GetCommandString() const
    {
        string op_str = (opcode == Union) ? "UNION" : "MEMBE";
        return op_str + " " + to_string(this->op1) + " " + to_string(this->op2);
    }
#endif
};

#define OP_ERROR false
#define OP_UNI_SUCCESS true
#define OP_UNI_IGNORE false
#define OP_MEM_IN true
#define OP_MEM_NOT_IN false

/*!
* @class Set
* @brief Ŀ���� ���� �����̳� Ŭ����
*/
class Sets
{
public:
    /// @short ������ �ʱ� ������� @p size + 1 ���� ������ ����
    Sets(const CountType& size): parents(size + 1)
    {
        /// �ʱ� ���¿��� ��� ���ҵǾ� �����Ƿ� ������ �θ�� �ڱ� �ڽ����� �����Ѵ�
        /// @warning 0 ���� n ���� �� **n + 1** ���� ���Ұ� ������
        for (IndexType i = 0; i < size + 1; ++i)
            this->parents[i] = i;
        return;
    };

    /// @short @p command �� ������ ���� ���� ������ ����
    bool Operation(const Command& command) 
    {

#ifdef PS_DEBUG
        cout << "= Processing Operation: " << command.GetCommandString() << '\n';
        cout << "- Current State:\n";
        this->PrintParents();
#endif // PS_DEBUG

        switch (command.opcode)
        {
        case Union:         return this->Op_Union(command.op1, command.op2);
        case Membership:    return this->Op_Membership(command.op1, command.op2);
        default:            break;
        }
        return OP_ERROR;
    };

    /*!
     * @brief @p op1 �� @p op2 �� ���� ���տ� ���ϴ��� Ȯ��
     * @return ���� ���տ� ���ϸ� true, �ƴϸ� false
    */
    bool Op_Membership(const OperandType& op1, const OperandType& op2) const
    {
        if (op1 == op2) 
            return OP_MEM_IN;
        if (this->GetRootParent(op1) == this->GetRootParent(op2)) 
            return OP_MEM_IN;
        else 
            return OP_MEM_NOT_IN;
    }

    /*!
     * @brief @p op1 �� ���Ե� ���հ� @p op2 �� ���Ե� ������ (��ĥ �ʿ䰡 �ִٸ�) ��ģ��. 
     * @return ������ ������ ���õǰų� ������ ��� false, ������ ������ ����Ǿ��ٸ� true
     * @pre @ref Op_Membership(const OperandType&, const OperandType&)
    */
    bool Op_Union(const OperandType& op1, const OperandType& op2)
    {
        // ���ʿ� op1�� op2�� ������ ��ĥ �ʿ䰡 ����.
        if (op1 == op2) 
            return OP_UNI_IGNORE;
        // ���ʿ� op1�� op2�� ���� ���տ� ���� ������ ��ĥ �ʿ䰡 ����.
        if (this->Op_Membership(op1, op2))
            return OP_UNI_IGNORE;

        // �� ������ ��ǥ�� ������ (�ֻ��� �θ� ���)
        const IndexType op1_root = this->GetRootParent(op1);
        const IndexType op2_root = this->GetRootParent(op2);

        // �� ���� ���� ���� ���� �θ� ���Ҵ��Ѵ�.
        // �� �κп��� op1_root�� op2_root�� ���� ���� ����
        if (op1_root > op2_root)
        {
            this->parents[op1_root] = op2_root;
            return OP_UNI_SUCCESS;
        }
        else
        {
            this->parents[op2_root] = op1_root;
            return OP_UNI_SUCCESS;
        }

        return OP_ERROR;
    }

    /// @short �� @p index �� ������ ��ǥ(�ֻ��� �θ� ���)�� �����´�.
    IndexType GetRootParent(const IndexType& index) const
    {
        const IndexType& current_parent = this->parents[index];
        if (current_parent == index) return index;
        return this->GetRootParent(current_parent);
    };
#ifdef PS_DEBUG
    void PrintParents() const
    {
        for (auto i = 0; i < this->parents.size(); ++i)
            cout << i << "[" << this->parents[i] << "] ";
        cout << '\n';
        return;
    }
#endif
public:
    /// @short ���պ��� �θ� ����ϴ� ���
    vector<IndexType> parents;
};


int main(void)
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

    /*!
    * @var n
    * @brief ������ �ʱ� ����
    * @note [1, 1e6]
    * @details {0}, {1}, ..., {n} ���� �� n+1 ���� ������ ������
    */
    CountType n; cin >> n;
    /*!
    * @var m
    * @note [1, 1e5]
    * @brief ������ ����
    */
    CountType m; cin >> m;

    vector<Command> commands;

    for (CountType command = 0; command < m; ++command)
    {
        int opcode; 
        /// a �� b�� n ���� ������, ���� ���� �ִ�.
        OperandType a, b;
        cin >> opcode >> a >> b;
        commands.push_back(Command(static_cast<Operation>(opcode), a, b));
    }

#ifdef PS_DEBUG
    for (const auto& command : commands) { cout << command.GetCommandString() << '\n'; }
#endif

    Sets set(n);
    for (const auto& command : commands)
    {
        /// ����ʸ� �� ����ϹǷ� ���������
        if (command.opcode == Membership)
        {
            string mem_result_string = set.Operation(command) ? "YES" : "NO";
            cout << mem_result_string << '\n';
        }
        else set.Operation(command);

    }

    return 0;
}

